rm -rf ../for_caffe/test_lmdb
GLOG_logtostderr=1 convert_imageset \
                 ./  \
                 ../for_caffe/test_labels.txt \
                 ../for_caffe/test_lmdb \
                 --shuffle \
                 -resize_height 250 \
                 -resize_width 250


