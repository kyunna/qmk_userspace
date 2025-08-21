# ------------------------------------------------------------
# Build Source
# Specifies the source files to include in the firmware build.
# ------------------------------------------------------------
SRC += pppp.c # main firmware logic

# ------------------------------------------------------------
# Boot Behavior
# Controls how the firmware behaves at startup.
# ------------------------------------------------------------
OS_DETECTION_ENABLE = yes     # enable host OS detection and set default layer
NO_USB_STARTUP_CHECK = yes    # skip USB check and start even without USB connection

# ------------------------------------------------------------
# Configuration Storage
# Controls dynamic configuration storage and VIA support.
# ------------------------------------------------------------
VIA_ENABLE = no               # disable VIA support
QMK_SETTINGS = no             # disable EEPROM QMK settings

# ------------------------------------------------------------
# Feature Enablement
# Enables additional QMK features.
# ------------------------------------------------------------
COMBO_ENABLE = yes            # enable combo key support
