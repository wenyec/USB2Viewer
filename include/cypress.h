/// \file cypress.h
/// Basic declarations for information regarding the Cypress FX2 part.

#pragma once

/// Vendor specific request code for Anchor Upload/Download
///
/// This one is implemented in the core

#define ANCHOR_LOAD_INTERNAL  0xA0


/// This command is not implemented in the core.  Requires firmware

#define ANCHOR_LOAD_EXTERNAL  0xA3

/// This is the highest internal RAM address for the AN2131Q

#define MAX_INTERNAL_ADDRESS  0x1B3F

#define INTERNAL_RAM(address) (address <= MAX_INTERNAL_ADDRESS)


/// EZ-USB Control and Status Register.  Bit 0 controls 8051 reset

#define CPUCS_REG_EZUSB    0x7F92
#define CPUCS_REG_FX2      0xE600
