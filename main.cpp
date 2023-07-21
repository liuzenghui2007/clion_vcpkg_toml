#include <QCoreApplication>
#include <QDebug>
// 这里的路径是什么，见每个库的github说明
// 比如vcpkg install spdlog，使用方法是：#include "spdlog/spdlog.h"
#include <iostream>
#include "toml.hpp"
#include "usb_info.h"

int main(int argc, char *argv[]) {
    QCoreApplication a(argc, argv);
    qDebug() << "Hello World";
    auto data = toml::parse("example.toml");
    auto &server = toml::find(data, "server");
    std::string ip = toml::find<std::string>(server, "ip");

    std::cout << "Hello, World!" << ip << std::endl;
    print_usb_info();
    return QCoreApplication::exec();
}
