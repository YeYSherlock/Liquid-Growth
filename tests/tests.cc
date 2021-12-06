#ifndef CATCH_CONFIG_MAIN
#  define CATCH_CONFIG_MAIN
#endif

#include "catch.hpp"
#include "vase.hpp"
#include "shiny.hpp"
#include "collection.hpp"

/////////////////////////////////////////////////////////////////////////////////////////////
//                                 Includes //
/////////////////////////////////////////////////////////////////////////////////////////////
#include <stdexcept>

TEST_CASE( "Build Vase" ) {
  Collection collection;
  collection.AddAtDate(9,20,2002,1);
  SECTION("Check Vase's template") {
      bool check = false;
      if(collection.GetVase()->GetVase() == collection.GetVase()->Getkalathos() && collection.GetVase()->GetVase() != collection.GetVase()->Getstamnos()){
        check = true;
      }
      REQUIRE( check == true);
  }

  SECTION("Check Vase's data") {
      bool check = false;
        if(collection.GetVase()->GetMonth() == 9 && collection.GetVase()->GetYear() == 2002 && collection.GetVase()->GetDate() == 20){
            check = true;
        }
      REQUIRE( check == true);
   }

   SECTION("Check Vase's characters") {
      bool check = false;
        if(collection.GetVase()->GetMood() == "~mood~" && collection.GetVase()->GetDay() == "~day~" && collection.GetVase()->GetWeather() == "~weather~"){
            check = true;
        }
      REQUIRE( check == true);
   }
}

TEST_CASE("Add shiny") {
    Vase* vase = new Vase(0, 12, 25, 2002, "Monday", "Happy", "Rain");
    vase->addShiny(25,"$","Happy Birthday!");
    SECTION("Check shiny object"){
        bool check = false;
        if(vase->GetShinyvector()[0]->unicode_ == "$" && vase->GetShinyvector()[0]->num_shiny_ == 25 && vase->GetShinyvector()[0]->log_ == "Happy Birthday!"){
            check = true;
        }
        REQUIRE( check == true);
    }

    SECTION("Count Shiny"){
        int count = 0;
        vector<vector<string>> temp_vec = vase->GetShinyvector()[0]->shiny_vec_;
        for(size_t i = 0; i < temp_vec.size(); i++){
            for(size_t j = 0; j < temp_vec[i].size(); j++){
                if(temp_vec[i][j] != " "){
                    count ++;
                }
            }
        }
        REQUIRE(count == 25);
    }
}

TEST_CASE("Check Vase's vector in collection"){
    Collection collection;
    collection.AddAtDate(9,20,2002,1);
    collection.AddAtDate(9,21,2002,1);
    collection.AddAtDate(12,5,2021,0);
    collection.AddAtDate(12,6,2021,0);

    SECTION("Current Vase"){
        bool check = false;
        Vase* vase = collection.GetVase();
        if(vase->GetVase() == vase->Getstamnos()){
           if(vase->GetDate() == 6 && vase->GetMonth() == 12 && vase->GetYear() == 2021){
               check = true;
           } 
        }
        REQUIRE(check == true);
    }

    SECTION("Previous Vase"){
        bool check = false;
        collection.Prev();
        collection.Prev();
         Vase* vase = collection.GetVase();
        if(vase->GetVase() == vase->Getkalathos()){
           if(vase->GetDate() == 21 && vase->GetMonth() == 9 && vase->GetYear() == 2002){
               check = true;
           } 
        }
        REQUIRE(check == true);
    }

    SECTION("Next Vase"){
        bool check = false;
        collection.Prev();
        collection.Prev();
        collection.Next();
        Vase* vase = collection.GetVase();
        if(vase->GetVase() == vase->Getstamnos()){
           if(vase->GetDate() == 5 && vase->GetMonth() == 12 && vase->GetYear() == 2021){
               check = true;
           } 
        }
        REQUIRE(check == true);
    }
}

TEST_CASE("Delete Shiny and undo"){
    SECTION("Vase Delete Shiny"){
        Vase* vase = new Vase(0, 12, 25, 2002, "Monday", "Happy", "Rain");
        vase->addShiny(25,"$","MP");
        vase->addShiny(20,"!","TRA");
        vase->DeleteLastShiny();
        REQUIRE(vase->GetShinyvector().size() == 1);
    }

    SECTION("Collection undo"){
        Collection collection;
        collection.AddAtDate(9,20,2002,1);
        collection.Add(25,"$","MP");
        collection.Undo();
        REQUIRE(collection.GetVase()->GetShinyvector().size() == 0);
    }
}

TEST_CASE("Save and Load"){
    bool check = false;
    Vase* original_vase = new Vase(0, 12, 25, 2002, "Monday", "Happy", "Rain");
    original_vase->SaveFile();
    Vase* loaded_vase = new Vase(1, 1, 1,2002, "Sunday", "Sad", "Sunny");
    loaded_vase->LoadFile("./storage/12_25_2002");
    if(loaded_vase->GetVase() == loaded_vase->Getstamnos()){
        if(loaded_vase->GetDate() == 25 && loaded_vase->GetMonth() == 12 && loaded_vase->GetYear() == 2002){
            check = true;
        } 
    }
    REQUIRE(check == true);
}