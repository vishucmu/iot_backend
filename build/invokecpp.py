import os
from flask import Flask, request, jsonify
from flask_restful import Resource, Api
from json import dumps, loads, load
from pathlib import Path
import json, csv, logging, pandas as pd
import http.client, urllib.request, urllib.parse, urllib.error, base64, re

app = Flask(__name__)
api = Api(app)

app.debug = True


class Jsonify(Resource):
    def get(self):
        # myCmd = './iot_risk_assessment'
        # os.system(myCmd)
        return response1()

    def post(self):
        process(request.get_json())
        myCmd = './iot_risk_assessment'
        os.system(myCmd)
        return response1()
        # return "csv2json"

def process(desc):
    # json_parsed = json.loads(str(desc))
    json_parsed = desc
    json_data = json_parsed["datarequest"]
    for infile in json_data:
        csv_name = infile['inputfile']['csvname']
        csv_data = infile['inputfile']['data']
        writetofile(csv_name,csv_data)
        print("*"*60)
        print(csv_name)
        print(csv_data)

def writetofile(csvname, csv_data):
    csvfile = open('../Data/' + csvname + '.csv', 'w')
    # logging.warning("CSV File::" + csvfile + " created")
        # create the csv writer object
    csvwriter = csv.writer(csvfile,lineterminator='\n')
    count = 0
    for row in csv_data:
        if count == 0:
            header = row.keys()
            # logging.warning("Writing:: " + header)
            csvwriter.writerow(header)
            count += 1
        csvwriter.writerow(row.values())
    csvfile.close()

def response():
    path = "../Results/"
    csv_rows = []
    data = []
    fileindex = 0
    for csvfile in os.listdir(path):
        filepath =  os.path.abspath(path+"/"+csvfile)
        fcsv = open(filepath, 'r')
        reader = csv.DictReader(fcsv)
        title = reader.fieldnames
        tempdata = {}
        for row in reader:
            csv_rows.extend([{title[i]:row[title[i]] for i in range(len(title))}])
            tempdata[csvfile] = csv_rows
        data.append(tempdata)
    return jsonify(data)

def response1():
    path = "../R3/"
    csv_rows = []
    data = []
    fileindex = 0
    for csvfile in os.listdir(path):
        filepath =  os.path.abspath(path+"/"+csvfile)
        csv_file = pd.DataFrame(pd.read_csv(filepath, sep = ",", header = 0, index_col = False))
        data.append((csv_file.to_json()))
    val = []
    val.append(data)
    return val

api.add_resource(Jsonify, '/jsontocsv')  # Route_1

if __name__ == '__main__':
    # app.run(host='0.0.0.0', port=5006, threaded=True)
    print(response())
