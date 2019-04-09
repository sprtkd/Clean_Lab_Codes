function [ new_img ] = gauss_avg( img, k, variance )
[row,col,channels]=size(img);
sum = double(zeros(row,col,1));

for nn=1:k
    noisy_img = double(imnoise(img,'gaussian',0,variance));
    if (nn==1)
        figure('Name','Noisy'),imshow(noisy_img);
        waitforbuttonpress;
    end
    for i=1:row
        for j=1:col
            sum(i,j) = sum(i,j) + noisy_img(i,j);
        end
    end
end

for i=1:row
    for j=1:col
        sum(i,j) = sum(i,j)/k;
    end
end

new_img = uint8(sum);


end

