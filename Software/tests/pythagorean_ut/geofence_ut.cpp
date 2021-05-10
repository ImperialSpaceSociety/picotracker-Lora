#include "CppUTest/TestHarness.h"
#include "CppUTestExt/MockSupport.h"

extern "C"
{
#include "LoRaMac.h"
#include "geofence.h"
#include "region_setting.h"
}

TEST_GROUP(Geofence_Polygon){
    void setup(){}

    void teardown(){
        mock().clear();
}
}
;

TEST(Geofence_Polygon, UK_test)
{
    Polygon_t poly = get_polygon(52, 0);
    CHECK_EQUAL(EU863870_EUROPE_polygon, poly);
}

TEST(Geofence_Polygon, Au_test)
{
    Polygon_t poly = get_polygon(-33.8696, 151.20695);
    CHECK_EQUAL(AU915928_AUSTRALIA_polygon, poly);
}

/**
 * @brief Test network key validity
 * 
 */
TEST(Geofence_Polygon, EU_network_key_test)
{
    network_keys_t eu_network_keys = get_network_keys(LORAMAC_REGION_EU868);

    CHECK_EQUAL(0xB1, eu_network_keys.AppSKey[0]);
}

/**
 * @brief Test network key validity
 * 
 */
TEST(Geofence_Polygon, test_array_compare)
{

    STRCMP_EQUAL("hello", "hello");
}