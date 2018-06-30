import pickle

fw = open('.\\caffe_word_labels.txt', 'w')
f = open('.\\chinese_labels', 'rb')
label_dict = pickle.load(f)
f.close()
for index in label_dict:
    print(str(index)+" "+str(label_dict[index]))
    fw.write(label_dict[index].strip()+"\n")
fw.close()