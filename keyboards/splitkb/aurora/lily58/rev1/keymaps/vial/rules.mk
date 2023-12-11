ENCODER_MAP_ENABLE = yes

# Vial setup
VIA_ENABLE = yes
VIAL_ENABLE = yes

# My setup
OLED_ENABLE = yes
COMBO_ENABLE = yes
KEY_OVERRIDE_ENABLE = yes
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = yes
ENCODER_ENABLE = yes

# Saving space on atmega32u4
ifeq ($(strip $(MCU)), atmega32u4)
    OLED_ENABLE = no
    MOUSEKEY_ENABLE = no
    COMBO_ENABLE = no
    KEY_OVERRIDE_ENABLE = no
endif

## build targets
# Liatris
# CONVERT_TO = liatris
# promicro
# BOOTLOADER = caterina
