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
    parser.add_argument('file_name_ref', help='name of the reference file')
    args = parser.parse_args()

    values = read_file(args.file_name)
    values_ref = read_file(args.file_name_ref)

    for row in range(len(values)):
        for col in range(len([row])):
            if values_ref[row][col] != values[row][col]:
                raise Exception('difference between ref and result')

    print('SUCCESS')
