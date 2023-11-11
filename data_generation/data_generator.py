import numpy as np
from random import randint


def get_number_of_layer(number_of_vertice):
    """
    Returns
    ----------
    int
    """
    lower_limit = 1
    upper_limit = number_of_vertice/2 if number_of_vertice/2 >= lower_limit else number_of_vertice-2
    return randint(lower_limit, upper_limit) + 2

def create_layer_index_list(number_of_vertice, number_of_layer):
    """
    Returns
    ----------
    List[int]
    """ 
    arr = [1] * number_of_layer; 
    for i in range(number_of_vertice-number_of_layer):
        arr[randint(1, number_of_layer-2)] += 1;        
    return arr

def get_access_index(cur_index, layer_index_list, flow_matrix):
    """
    Returns
    ----------
    List[int]
    """
    index_limit_list = [layer_index_list[x] + sum(layer_index_list[:x]) for x in range(len(layer_index_list))]
    cur_layer = [cur_index < x for x in index_limit_list].index(True)
    access_index_list = [x for x in range(index_limit_list[cur_layer], index_limit_list[cur_layer+1])]
    for index in access_index_list:
        if flow_matrix[index][cur_index] != 0:
            access_index_list.remove(index)
    return access_index_list

def create_random_list(length):
    """
    Returns
    ----------
    List[int]
    
    Notes
    ----------
    Retry if created all 0 list
    """
    while True:
        value_list = np.random.randint(low=0, high=10, size=length)
        # print(value_list)
        if np.any(value_list):
            break
    return iter(value_list)

def write_output(outfile, number_of_vertice, flow_matrix):
    out_list = str(number_of_vertice) + "\n"
    for row_index in range(number_of_vertice-1):
        for column_index in range(number_of_vertice):
            if flow_matrix[row_index][column_index]:
                out_list+= f"{row_index} {column_index} {flow_matrix[row_index][column_index]}\n"
    with open(outfile, 'w') as f:
        f.write(out_list)


def run(number_of_vertice, outfile):
    number_of_layer = get_number_of_layer(number_of_vertice)
    layer_index_list = create_layer_index_list(number_of_vertice, number_of_layer)
    flow_matrix = np.zeros(shape=(number_of_vertice, number_of_vertice), dtype=np.int8)
    print(f"Number of layer: {number_of_layer}")
    print(f"Layer index list {layer_index_list}")
    for row_index in range(number_of_vertice-1):
        access_index_list = get_access_index(row_index, layer_index_list, flow_matrix)        
        if len(access_index_list) == 0:
            continue
        capacity_list = create_random_list(len(access_index_list))
        for column_index in range(number_of_vertice):
            if column_index in access_index_list:
                flow_matrix[row_index][column_index] = next(capacity_list)
            else:
                flow_matrix[row_index][column_index] = 0
    write_output(outfile, number_of_vertice, flow_matrix)
    

for i in range(1000):
    print(f"Running index {i}")
    run(100, f'data/test_{i}.txt')