    #include "Restaurant.h"

    unsigned int Restaurant::add_product(std::string const& name, units unit, std::string const& allergens, unsigned int quantity){
        Product * p = new Product(name, unit, allergens, quantity);
        return pantry.add_data(p);
    }

    unsigned int Restaurant::add_dish(unsigned int id, std::string const& name, dish_type type, Money const& price, bool is_vegan, std::vector<Ingredient> & ingredients){
        Dish * d = new Dish(id, name, type, price, is_vegan, ingredients, {}, &(this->pantry));
        return menu.add_data(d);
    }

    unsigned int Restaurant::add_cook(std::string const& name , std::string const& surname, Addres const& address, Money const& salary, bool is_chef){
        Cook * c = new Cook(name, surname, address, salary, is_chef);
        return employee_database.add_data(c);
    }

    unsigned int Restaurant::add_deliverer(std::string const& name, std::string const& surname, Addres const& address, Money const& salary){
        Deliverer * d = new Deliverer(name, surname, address, salary);
        return employee_database.add_data(d);
    }


    unsigned int Restaurant::add_manager(std::string const& name, std::string const& surname, Addres const& address, Money const& salary){
        Manager * m = new Manager(name, surname, address, salary);
        return employee_database.add_data(m);
    }


    unsigned int Restaurant::add_waiter(std::string const& name, std::string const& surname, Addres const& address, Money const& salary){
        Waiter * w = new Waiter(name, surname, address, salary);
        return employee_database.add_data(w);
    }

    unsigned int Restaurant::add_delivery_order(std::vector<unsigned int> ordered_dishes, unsigned int deliverer_id, Addres const& address){
        DeliveryOrder * dor = new DeliveryOrder(ordered_dishes, deliverer_id, address);
        return active_orders.add_data(dor);
    }

    unsigned int Restaurant::add_on_site_order(std::vector<unsigned int> ordered_dishes, unsigned int waiter_id, unsigned int table_id){
        OnSiteOrder * dor = new OnSiteOrder(ordered_dishes,  waiter_id, table_id);
        return active_orders.add_data(dor);
    }


    void Restaurant::remove_product(unsigned int id){
        std::vector<Dish *> dishes= this->get_all_dishes();
        for(auto dish:dishes){
            for(auto ing:dish->get_ingredients()){
                if(ing.stock_id == id) throw ProductCurrentlyInDish;
            }
        }
        pantry.remove_data(id);
    }


    void Restaurant::remove_dish(unsigned int id){
        std::vector<BaseOrder *> orders = this->get_all_active_orders();
        for (auto order:orders){
            for(auto dish:order->get_ordered_dishes()){
                if(dish == id) throw DishCurrentlyInOrder;
            }
        }
        orders = this->get_all_orders_from_history();
        for (auto order:orders){
            for(auto dish:order->get_ordered_dishes()){
                if(dish == id) throw DishCurrentlyInOrder;
            }
        }
        menu.remove_data(id);
    }

    void Restaurant::remove_employee(unsigned int id){
        employee_database.remove_data(id);
        std::vector<BaseOrder *> orders = this->get_all_active_orders();
        for (auto order:orders){
            if(order->get_employee_id() == id) throw EmployeeCurrentlyWithOrder;
        }
        orders = this->get_all_orders_from_history();
        for (auto order:orders){
            if(order->get_employee_id() == id) throw EmployeeCurrentlyWithOrder;
        }
    }

    void Restaurant::remove_active_order(unsigned int id){
        BaseOrder * order = get_active_order(id);
        for(auto dish:order->get_ordered_dishes()){
            for(auto ingridient:get_dish(dish)->get_ingredients()){
                get_product(ingridient.stock_id)->release(ingridient.quantity);
            }
        }
        active_orders.remove_data(id);
    }

    void Restaurant::add_dish_to_order(unsigned int order_id, int dish_id){
        BaseOrder * order = get_active_order(order_id);
        try{
            for(auto ingridient:get_dish(dish_id)->get_ingredients()){
                    get_product(ingridient.stock_id)->reserve(ingridient.quantity);
            }
            order->add_dish(dish_id);
        }
            catch(std::invalid_argument & e){
            throw NotEnoughtProductInPantry;
        }
    }

    void Restaurant::remove_dish_from_order(unsigned int order_id, int position){
        BaseOrder * order = get_active_order(order_id);
        for(auto ingridient:get_dish(order->get_ordered_dishes()[position])->get_ingredients()){
                get_product(ingridient.stock_id)->release(ingridient.quantity);
        }
        order->remove_dish(position);
    }

    Money Restaurant::get_active_order_value(unsigned int order_id){
        BaseOrder * order = get_active_order(order_id);
        Money m;
        for (size_t i=0;  i<order->get_ordered_dishes().size(); i++){
            m += get_dish(order->get_ordered_dishes()[i])->get_price();
        }
        return m;
    }

    void Restaurant::mark_order_as_done(unsigned int order_id){
        BaseOrder * order = get_active_order(order_id);
        active_orders.remove_data_without_deleting(order_id);
        orders_history.add_data_with_id(order);
        for(auto dish:order->get_ordered_dishes()){
            for(auto ingridient:get_dish(dish)->get_ingredients()){
                get_product(ingridient.stock_id)->use_product(ingridient.quantity);
            }
        }
    }

    void Restaurant::generate_lunch_menu()
    {
        ofstream file;
        file.open ("lunch.txt");
        std::time_t t = std::time(0);
        std::tm* now = std::localtime(&t);
        file << "Lunch menu - " << (now->tm_year + 1900) << '.'
        << (now->tm_mon + 1) << '.' <<  now->tm_mday << "\n";

        srand (time(NULL));
        string starter="", main="", dessert="";
        int iter = 0;
        while((starter == "" || main == "" || dessert == "") && iter < 1000)
        {
            int random = rand() % menu.size() + 1001;
            if (menu.operator[](random)->get_enum_dish_type() < 2 && starter == "")
                starter = menu.operator[](random)->get_name();
            if (menu.operator[](random)->get_enum_dish_type() == 2 && main == "")
                main = menu.operator[](random)->get_name();
            if (menu.operator[](random)->get_enum_dish_type() == 3 && dessert == "")
                dessert = menu.operator[](random)->get_name();
            iter++;
        }
        if (iter == 1000) throw NotEnoughDishType;
        file << "Przystawka / zupa:\n" << starter;
        file << "\nDanie główne:\n" << main;
        file << "\nDeser:\n" << dessert;
        file.close();
    }

    Json::Value Restaurant::parse_to_json(){
        Json::Value restaurant;
        restaurant["id"] = restaurant_id;
        restaurant["name"] = name;
        restaurant["address"] = address.parse_to_json();
        restaurant["pantry"] = pantry.parse_to_json();
        restaurant["menu"] = menu.parse_to_json();
        restaurant["employees"] = employee_database.parse_to_json();
        restaurant["active_orders"] = active_orders.parse_to_json();
        restaurant["order_history"] = orders_history.parse_to_json();
        return restaurant;
    }