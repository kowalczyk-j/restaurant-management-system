cmake_minimum_required(VERSION 3.16)

project(app VERSION 1.0 LANGUAGES CXX)

add_compile_options(-Wall -Wextra -pedantic -Werror)

include(FetchContent)
FetchContent_Declare(
   googletest
   GIT_REPOSITORY      https://github.com/google/googletest.git
   GIT_TAG main
)
FetchContent_Declare(
   jsoncpp
   GIT_REPOSITORY      https://github.com/open-source-parsers/jsoncpp
   GIT_TAG master
)
FetchContent_MakeAvailable(googletest)
FetchContent_MakeAvailable(jsoncpp)

set(MENU src/dish_menu/Dish.h src/dish_menu/Dish.cpp)
set(EMPLOYEES src/employees/Employee.h src/employees/Employee.cpp src/employees/Cook.h src/employees/Deliverer.h src/employees/Manager.h  src/employees/Waiter.h)
set(ORDER src/order/BaseOrder.h src/order/DeliveryOrder.h src/order/OnSiteOrder.h)
set(PANTRY src/pantry/Product.h src/pantry/Stock.h)
set(RESTAURANT src/restaurant/Restaurant.h)
set(UTILS src/utils/Address.h src/utils/Money.h src/utils/Money.cpp)
set(DATABASE src/Database.h)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(tests test.cpp ${MENU} ${EMPLOYEES} ${ORDER} ${PANTRY} ${RESTAURANT} ${UTILS})
add_executable(app main.cpp  ${MENU} ${EMPLOYEES} ${ORDER} ${PANTRY}  ${UTILS} ${DATABASE})

target_link_libraries(tests PUBLIC gtest_main jsoncpp_lib)
target_link_libraries(app jsoncpp_lib)
