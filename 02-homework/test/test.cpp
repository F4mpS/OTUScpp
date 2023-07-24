#include <iostream>
#include <sstream>
#include <string>
#include <tuple>
#include <gtest/gtest.h>


#include "../src/utilities/split.h"
#include "../src/utilities/sort.h"
#include "../src/utilities/filter.h"

#include "../src/ip.h"

std::vector<my::ip_adress> IP_LIST =
{               
    { 185,  46,  85, 204 },
    {  46, 251, 197,  23 },
    {  68,  46, 218, 208 },
    {   1,  87, 203, 225 },
    {  46,  70, 113,  73 },
    { 185,  46,  85,  78 },
    {  46, 223, 254,  56 },
    { 185,  46,  86,  22 },
    {   1,  70,  44, 170 },
    {  46,  70, 147,  26 },
    {  46,  70,  29,  76 },
    {   1, 231,  69,  33 },
    {  46,  70, 225,  39 }       
};
     




class IpFilterData :
    public ::testing::TestWithParam
    <
        std::tuple
        <
            std::vector<my::ip_adress>,
            std::function
            <
                std::vector<my::ip_adress>(const std::vector<my::ip_adress>&)
            >,
            std::vector<my::ip_adress> 
        >
    >
{};

TEST_P(IpFilterData, IpFilterTest) 
{
    const std::vector<my::ip_adress> raw_ip_list = std::get<0>(GetParam());
    const std::function<std::vector<my::ip_adress>(const std::vector<my::ip_adress>&)> TestFilter = std::get<1>(GetParam());
    const std::vector<my::ip_adress> correct_ip_pool = std::get<2>(GetParam());
    
    // Preparation
    std::vector<my::ip_adress> ip_pool;
    for (my::ip_adress ip : raw_ip_list)
    {
        ip_pool.push_back(ip);
    }
    my::LexicographicallySort(ip_pool);
    
    // Test
    std::vector<my::ip_adress> filtred_pool = TestFilter(ip_pool);
    ASSERT_EQ(filtred_pool.size(), correct_ip_pool.size()) << "IP lists have different sizes!!!";
    
    for (std::size_t i = 0; i < correct_ip_pool.size(); i++)
    {
        ASSERT_TRUE(my::CompareIp(filtred_pool[i], correct_ip_pool[i]));
    }
}

INSTANTIATE_TEST_SUITE_P
(
    IpFilterTestCase,
    IpFilterData,
    ::testing::Values
    (
        std::make_tuple
        (
            IP_LIST,
            my::Filter_1,
            std::vector<my::ip_adress>
            {
                {   1, 231,  69,  33 },
                {   1,  87, 203, 225 },
                {   1,  70,  44, 170 },
            }
        ),
        std::make_tuple
        (
            IP_LIST,
            my::Filter_46_70,
            std::vector<my::ip_adress>
            {
                {  46,  70, 225,  39 },
                {  46,  70, 147,  26 },
                {  46,  70, 113,  73 },
                {  46,  70,  29,  76 }
            }
        ),
        std::make_tuple
        (
            IP_LIST,
            my::Filter_any46,
            std::vector<my::ip_adress>
            {
                { 185,  46,  86,  22 },
                { 185,  46,  85, 204 },
                { 185,  46,  85,  78 },
                {  68,  46, 218, 208 },
                {  46, 251, 197,  23 },
                {  46, 223, 254,  56 },
                {  46,  70, 225,  39 },
                {  46,  70, 147,  26 },
                {  46,  70, 113,  73 },
                {  46,  70,  29,  76 },
            }
        )
    )
);

int main(int argc, char* argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
