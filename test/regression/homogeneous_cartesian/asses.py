import csv
import argparse

def read_file(file_name):
    values = []

    with open(file_name, newline='') as csvfile:
        reader = csv.reader(csvfile, delimiter=',')

        for row in reader:
            vals_row = []

            for elem in row:
                vals_row.append(float(elem))

            values.append(vals_row)

    return values

if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('file_name', help='name of the result file')
    args = parser.parse_args()

    values = read_file(args.file_name)

    if values[0][0] != 100:
        raise Exception("temperature difference too big")
    elif values[1][0] != 100:
        raise Exception("temperature difference too big")
    elif values[2][0] != 100:
        raise Exception("temperature difference too big")
    elif values[3][0] != 200:
        raise Exception("temperature difference too big")
    elif values[4][0] != 200:
        raise Exception("temperature difference too big")
    elif values[5][0] != 200:
        raise Exception("temperature difference too big")
    elif values[6][0] != 300:
        raise Exception("temperature difference too big")
    elif values[7][0] != 300:
        raise Exception("temperature difference too big")
    elif values[8][0] != 300:
        raise Exception("temperature difference too big")

    print('SUCCESS')
