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
  // clang-format off
}



