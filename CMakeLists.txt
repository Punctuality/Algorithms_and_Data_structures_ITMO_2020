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

add_executable(algos_3_1067 "tasks/common_3/disk_tree_1067.cpp")
add_executable(algos_3_1494 "tasks/common_3/mono_pool_1494.cpp")
add_executable(algos_3_1521 "tasks/common_3/millitary_training_1521.cpp")
add_executable(algos_3_1628 "tasks/common_3/white_stripes_1628.cpp")
add_executable(algos_3_1650 "tasks/common_3/billionares_1650.cpp")

add_executable(algos_4_1080 "tasks/common_4/map_coloring_1080.cpp")
add_executable(algos_4_1450 "tasks/common_4/russian_pipelines_1450.cpp")
add_executable(algos_4_1160 "tasks/common_4/network_1160.cpp")

add_executable(extra_1 "tasks/extra/fenwick_tree.cpp")
