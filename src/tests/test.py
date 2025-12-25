def point_in_triangle(point):
    return True

tile_size = 5
tile_count = 5

for i in range(0, tile_count * tile_size, tile_size):
    for j in range(0, tile_count * tile_size, tile_size):
        tile_v0 = [j, i]
        tile_v1 = [j + tile_size, i]
        tile_v2 = [j + tile_size, i + tile_size]
        tile_v3 = [j, i + tile_size]

        if point_in_triangle(tile_v0) and point_in_triangle(tile_v1) and point_in_triangle(tile_v2) and point_in_triangle(tile_v3):
            print(f"tile at {j}, {i} is rendered")
            pass
        else:
            print(f"tile at {j}, {i} is skipped")
            #skip the tile
            pass
