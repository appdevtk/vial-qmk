#!/usr/bin/env python3
"""Exercise the real layer callback and source keymaps with a native C harness.

This does not build firmware or emulate the split transport, EEPROM or USB.
"""

from pathlib import Path
import os
import re
import shlex
import subprocess
import tempfile


KEYMAP = Path(__file__).resolve().parents[1]
ROOT = next(parent for parent in KEYMAP.parents if (parent / "quantum/action_layer.c").is_file())


def function(source, name):
    match = re.search(r"^[\w *]+\b" + name + r"\([^\n]*\)\s*\{.*?^\}", source, re.M | re.S)
    if match is None:
        raise AssertionError(f"Cannot extract {name}")
    return match.group()


def main():
    source = (KEYMAP / "keymap.c").read_text()
    header = (KEYMAP / "lily58_vial.h").read_text()
    enum = re.search(r"enum layers\s*\{.*?\};", header, re.S).group()
    names = re.findall(r"_\w+", enum)
    thumb_rows = {}
    for name, body in re.findall(r"\[(_\w+)\]\s*=\s*LAYOUT\((.*?)\n\s*\)", source, re.S):
        keys = [key.strip() for key in body.split(",")]
        assert len(keys) == 58, name
        values = []
        for position in (52, 55):
            key = keys[position]
            if key == "_______":
                values.append("-1")
            else:
                match = re.fullmatch(r"MO\((\w+)\)", key)
                assert match, (name, position, key)
                values.append(match.group(1))
        thumb_rows[name] = "{" + ", ".join(values) + "}"
    assert len(thumb_rows) == 9
    c = """#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
typedef uint32_t layer_state_t;
layer_state_t default_layer_state;
"""
    c += enum + "\n"
    c += function((ROOT / "quantum/action_layer.c").read_text(), "update_tri_layer_state") + "\n"
    c += function(source, "layer_state_set_user") + "\n"
    c += "static const int8_t thumbs[9][2] = {\n"
    c += "".join(f"    [{name}] = {thumb_rows[name]},\n" for name in names)
    c += "};\n"
    c += r"""
static uint8_t press_layer(layer_state_t state, uint8_t key) {
    layer_state_t active = state | default_layer_state;
    for (int8_t layer = 8; layer >= 0; --layer) {
        if ((active & (1U << layer)) && thumbs[layer][key] >= 0) {
            return thumbs[layer][key];
        }
    }
    assert(thumbs[0][key] >= 0);
    return thumbs[0][key];
}

static layer_state_t expected(uint8_t held, bool windows) {
    layer_state_t state = 0;
    if (held & 1) state |= (1U << _LOWER_MAC) | (windows ? 1U << _LOWER_WIN : 0);
    if (held & 2) state |= (1U << _RAISE_MAC) | (windows ? 1U << _RAISE_WIN : 0);
    if (held == 3) state |= 1U << _ADJUST_1;
    return state;
}

int main(void) {
    unsigned scenarios = 0;
    for (uint8_t base = _DEFAULT_MAC; base <= _CODENGLISH; ++base) {
        default_layer_state = 1U << base;
        for (uint8_t first = 0; first < 2; ++first) {
            for (uint8_t release_first = 0; release_first < 2; ++release_first) {
                layer_state_t state = 0;
                uint8_t held = 0;
                uint8_t pressed[2];
                for (uint8_t step = 0; step < 2; ++step) {
                    uint8_t key = first ^ step;
                    pressed[key] = press_layer(state, key);
                    held |= 1U << key;
                    state = layer_state_set_user(state | (1U << pressed[key]));
                    assert(state == expected(held, base == _DEFAULT_WIN));
                }
                for (uint8_t step = 0; step < 2; ++step) {
                    uint8_t key = release_first ^ step;
                    held &= ~(1U << key);
                    state = layer_state_set_user(state & ~(1U << pressed[key]));
                    assert(state == expected(held, base == _DEFAULT_WIN));
                }
                assert(state == 0);
                ++scenarios;
            }
        }
    }
    assert(layer_state_set_user(1U << _ADJUST_2) == (1U << _ADJUST_2));
    printf("Layer checks passed: %u press/release scenarios across 3 base layers.\n", scenarios);
    return 0;
}
"""
    with tempfile.TemporaryDirectory(prefix="lily58-keymap-check-") as directory:
        path = Path(directory)
        (path / "check.c").write_text(c)
        compiler = shlex.split(os.environ.get("CC", "cc"))
        subprocess.run(compiler + ["-std=c11", "-Wall", "-Wextra", "-Werror", str(path / "check.c"), "-o", str(path / "check")], check=True)
        subprocess.run([str(path / "check")], check=True)


if __name__ == "__main__":
    main()
