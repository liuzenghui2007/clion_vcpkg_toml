//
// Created by zenghui on 2023/7/21.
//
#include "usb_info.h"
#include <iostream>

void print_usb_info() {
    // Initialize libusb
    if (libusb_init(NULL) != 0) {
        std::cerr << "Failed to initialize libusb." << std::endl;
        return;
    }

    // Get the list of USB devices
    libusb_device** device_list;
    ssize_t count = libusb_get_device_list(NULL, &device_list);
    if (count < 0) {
        std::cerr << "Failed to get USB device list." << std::endl;
        libusb_exit(NULL);
        return;
    }

    // Iterate through the devices and print information
    for (ssize_t i = 0; i < count; ++i) {
        libusb_device* device = device_list[i];
        struct libusb_device_descriptor descriptor;
        if (libusb_get_device_descriptor(device, &descriptor) == 0) {
            std::cout << "Device #" << i + 1 << std::endl;
            std::cout << "Vendor ID: 0x" << std::hex << descriptor.idVendor << std::dec << std::endl;
            std::cout << "Product ID: 0x" << std::hex << descriptor.idProduct << std::dec << std::endl;
            std::cout << "Bus Number: " << libusb_get_bus_number(device) << std::endl;
            std::cout << "Device Address: " << libusb_get_device_address(device) << std::endl;
            std::cout << std::endl;
        }
    }

    // Free the device list
    libusb_free_device_list(device_list, 1);

    // Deinitialize libusb
    libusb_exit(NULL);
}
