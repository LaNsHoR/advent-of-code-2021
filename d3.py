file = open('d3_data.txt', "r")
raw_data = file.readlines()
file.close()

# Common Utils ===============================================

def parse_data( data ):
    return { "base":data.strip(), "volatile": data.strip() }

def common_bit( data, key, i = 0 ):
    one_count = 0
    for word in data:
        if word[key][i] == '1':
            one_count += 1
    if one_count > len(data)/2.0:
        return 1
    if one_count < len(data)/2.0:
        return 0
    return 2

# Part 1 =====================================================

def solver_1( data ):
    gamma = ''
    size = len(data[0]["base"])
    for i in range( size ):
        gamma += '1' if common_bit(data, "base", i) else '0'
    gamma = int(gamma, 2)
    epsilon = ~gamma
    epsilon &= 0xFFFFFFFF >> ( 32 - size )
    print(gamma, epsilon, gamma * epsilon)

# Part 2 =====================================================

def process_queue( queue, criteria):
    while( len(queue) > 1 ):
        new_queue = []
        bit = common_bit( queue, "volatile" )
        for word in queue:
            first = word["volatile"][0]
            if( (bit == 0 and first == criteria[0]) or
                (bit == 1 and first == criteria[1]) or
                (bit == 2 and first == criteria[2]) ):              
                    new_queue.append( { "base":word["base"], "volatile":word["volatile"][1:]} )
        queue = new_queue
    return queue[0]["base"]

def solver_2( queue ):
    o2 = int( process_queue(queue, ['0', '1', '1']), 2)
    co2 = int( process_queue(queue, ['1', '0', '0']), 2)
    print( o2, co2, o2*co2 )

# Go go go! ==================================================

queue = map( parse_data, raw_data )
solver_1( queue )
solver_2( queue )
