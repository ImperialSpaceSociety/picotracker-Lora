#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "LoRaMac.h"
#include "geofence.h"
}


TEST_GROUP(Geofence_Polygon)
{
    void setup() {
    }


    void teardown() {
        mock().clear();
    }

};


TEST(Geofence_Polygon, UK_test)
{
    Polygon_t poly = get_polygon(52,0);
    CHECK_EQUAL(EU863870_EUROPE_polygon, poly);
}


TEST(Geofence_Polygon, Au_test)
{
    Polygon_t poly = get_polygon(-33.8696, 151.20695);
    CHECK_EQUAL(AU915928_AUSTRALIA_polygon, poly);
}



