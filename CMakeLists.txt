cmake_minimum_required(VERSION 3.15)
project(Algos_Tasks)

set(CMAKE_CXX_STANDARD 14)

add_executable(algos_1_2025 "tasks/common_1/wall_on_wall_2025.c")
add_executable(algos_1_1005 "tasks/common_1/bunch_of_stones_1005.c")
add_executable(algos_1_1155 "tasks/common_1/duons_1155.c")
add_executable(algos_1_1296 "tasks/common_1/hyperjump_1296.c")
add_executable(algos_1_1296_dnc "tasks/common_1/hyperjump_1296_dnc.c")
add_executable(algos_1_1401 "tasks/common_1/players_1401.c")

add_executable(algos_2_1207 "tasks/common_2/median_of_surface_1207.cpp")
add_executable(algos_2_1322 "tasks/common_2/spy_1322.cpp")
add_executable(algos_2_1444 "tasks/common_2/feed_elepophant_1444.cpp")
add_executable(algos_2_1604 "tasks/common_2/land_of_fools_1604.cpp")
add_executable(algos_2_1726 "tasks/common_2/the_one_who_visits_1726.cpp")