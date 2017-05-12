rm -rf ../for_caffe/train_lmdb
GLOG_logtostderr=1 convert_imageset \
                 ./  \
                 ../for_caffe/train_labels.txt \
                 ../for_caffe/train_lmdb \
                 --shuffle \
                 -resize_height 250 \
                 -resize_width 250


