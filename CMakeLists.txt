cmake_minimum_required(VERSION 3.16)

project(app VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -Werror)



set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_PREFIX_PATH /home/kajotello/Qt/5.15.2/gcc_64/lib/cmake/Qt5)
set(CMAKE_AUTOUIC ON)

set(MENU src/dish_menu/Dish.h src/dish_menu/Dish.cpp)
set(EMPLOYEES src/employees/Employee.h src/employees/Employee.cpp src/employees/Cook.h src/employees/Deliverer.h src/employees/Manager.h  src/employees/Waiter.h)
set(ORDER src/order/BaseOrder.h src/order/DeliveryOrder.h src/order/OnSiteOrder.h)
set(PANTRY src/pantry/Product.h)
set(RESTAURANT src/restaurant/Restaurant.h)
set(UTILS src/utils/Address.h src/utils/Money.h src/utils/Money.cpp)

set(MAINWINDOW gui/main_window/mainwindow.cpp gui/main_window/mainwindow.h)
set(CHANGEADDRESS gui/change_address/changeaddresswindow.h gui/change_address/changeaddresswindow.cpp)
set(ADDDISH gui/add_dish/adddish.h)
set(ADDORDER gui/add_order/addorder.h)
set(ADDEMPLOYEE gui/add_employee/addemployee.h gui/add_employee/addemployee.cpp)
set(CHANGENAME gui/change_name/changename.h gui/change_name/changename.cpp)
set(CHANGESALARY gui/change_salary/changesalary.h gui/change_salary/changesalary.cpp)
set(CHANGESURNAME gui/change_surname/changesurname.h gui/change_surname/changesurname.cpp)
set(ADDPRODUCT gui/add_product/addproduct.h gui/add_product/addproduct.cpp)
set(ADDINGRIDIENT gui/add_ingridient/addingridient.h)
set(CHANGECATEGORY gui/change_category/changecategory.h gui/change_category/changecategory.cpp)
set(ADDMENUDISH gui/add_menu_dish/addmenudish.h)
set(ADDOSORDER gui/add_onsite_order/addosorder.h)




find_package(Qt5 5.15 COMPONENTS Quick Gui Widgets QuickWidgets QmlImportScanner Qml REQUIRED)
find_package(jsoncpp REQUIRED)

add_executable(app main.cpp ${MENU} ${EMPLOYEES} ${ORDER} ${PANTRY} ${RESTAURANT} ${UTILS})
add_executable(guiApp gui/main.cpp ${MAINWINDOW} ${CHANGEADDRESS} ${ADDOSORDER} ${ADDMENUDISH} ${DATABASE} ${ADDDISH} ${ADDORDER} ${ADDEMPLOYEE} ${CHANGECATEGORY} ${ADDINGRIDIENT} ${CHANGENAME} ${CHANGESURNAME} ${CHANGESALARY} ${ADDPRODUCT} ${MENU} ${EMPLOYEES} ${ORDER} ${PANTRY} ${RESTAURANT} ${UTILS})

target_link_libraries(app jsoncpp_lib)

target_link_libraries(guiApp PUBLIC jsoncpp_lib Qt5::Quick Qt5::Gui Qt5::Widgets Qt5::QuickWidgets )
qt5_import_qml_plugins(guiApp)
