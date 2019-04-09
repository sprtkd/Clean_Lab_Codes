clc;
img=load('l256.dat');
img=uint8(img);
figure('Name','Actual'),imshow(img);
waitforbuttonpress;

noisy_img = img_manipulate(img, 20, 50);
figure('Name','Noisy'),imshow(noisy_img);
waitforbuttonpress;

new_img = spatial_mean_filter_thresh(noisy_img,3, 20);
figure('Name','MeanFiltered thresh'),imshow(new_img);
waitforbuttonpress;