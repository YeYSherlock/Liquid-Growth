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

TEST_CASE("SHINY") {

}