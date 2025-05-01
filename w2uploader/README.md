# W2 Uploader

This is an uploader for the W2R2 chips implemented by C++.
The serial port communication is done using [itas109's CSerialPort](https://github.com/itas109/CSerialPort) library.

## Usage

1. Connect the W2R2 chip (usually the W2 develop board) to your computer using a USB-to-serial adapter.
2. Download the latest release of the `w2uploader_<version>.zip` from
   the [release page](https://github.com/PramSin/W2/releases).
3. Unzip the downloaded file and navigate to the `bin` directory.
4. Run the `w2uploader.exe` file like below:
   ```bash
   ./w2uploader test.bin COM1
   ```
   Replace `test.bin` with the path to the firmware file you want to upload.
   And replace `COM1` with the serial port your W2R2 chip is connected to.
   The full help message is:
   ```text
   Usage:
   w2uploader <bin_path> <port_name> [OPTIONS]
   OPTIONS:
     -h, --help       Show this help message
     -v, --visible    Show detailed information
     -r, --run        Run the program immediately after the upload
         --no-reset   Upload the program immediately without waiting for the reset of the board
   ```
