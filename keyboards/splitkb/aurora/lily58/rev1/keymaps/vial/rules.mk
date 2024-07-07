ENCODER_MAP_ENABLE = yes

# Vial setup
VIA_ENABLE = yes
VIAL_ENABLE = yes

# Stuff
OS_DETECTION_ENABLE = yes
WPM_ENABLE = yes
REPEAT_KEY_ENABLE = yes
CAPS_WORD_ENABLE = yes
COMMAND_ENABLE = no
DEFERRED_EXEC_ENABLE = yes

# RGB
RGB_MATRIX_ENABLE = yes
RGBLIGHT_ENABLE = no
VIALRGB_ENABLE = yes

# OLED
OLED_ENABLE = yes
OLED_DRIVER = ssd1306

# Saving space on atmega32u4
ifeq ($(strip $(CONVERT_TO)), )
    OLED_ENABLE = no
    MOUSEKEY_ENABLE = no
    COMBO_ENABLE = no
    KEY_OVERRIDE_ENABLE = no
endif

## build targets
# Liatris
CONVERT_TO = liatris
# promicro
# BOOTLOADER = caterina
