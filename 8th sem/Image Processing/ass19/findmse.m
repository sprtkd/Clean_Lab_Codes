function [ mse_out ] = findmse( img_1, img_2 )

    if size(img_1) ~= size(img_2)
        mse_out=1;
        disp('size mismatch');
        return
    end
    [row,col,channels]=size(img_1);
    sum=double(0);
    for i=1:row
        for j=1:col
            sum = sum + double((img_1(i,j) - img_2(i,j)))^2;
        end
    end
    
    mse_out = double(sum)/(row*col);
    
end

