function [ man_img ] = img_manipulate( img, p, q )
[row,col,channels]=size(img);

man_img = zeros(row,col,1);
rand_bit_mat= zeros(row,col);

goal = int64(double(row*col) *double(p)/100);

rand_bit_mat(randperm(numel(rand_bit_mat), goal)) = 1;
for i=1:row
    for j=1:col
        if rand_bit_mat(i,j) == 1
            if randi([0,1]) == 1
                man_img(i,j) = img(i,j) + (double(img(i,j))*(double(q)/100));
            else
                man_img(i,j) = img(i,j) - (double(img(i,j))*(double(q)/100));
            end
        else
            man_img(i,j)=img(i,j);
        end
        
        if man_img(i,j) < 0
            man_img(i,j)=0;
        end
        if man_img(i,j) >255
            man_img(i,j) =255;
        end
    end
end

man_img = uint8(man_img);
endfunction

