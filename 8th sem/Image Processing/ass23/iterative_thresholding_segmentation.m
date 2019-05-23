pwdir  = pwd;

if ispc()
	indices = strfind(pwdir,'\');
	pwdir = pwdir(1:indices(end)-1);
	img = load(strcat(pwdir, '\image\l256.dat'));

else
	idcs   = strfind(pwdir,'/');
	pwdir = pwdir(1:idcs(end)-1);
	img = load(strcat(pwdir, '/image/l256.dat'));
end

dim = size(img);

Told = 0.0;
Tnew = 0.0;

a = 0.0;
b = 0.0;

for i = 1:10
    for j = 1:10
        a = a + img(i,j) + img(257 - i, j) + img(i, 257 - j) + img(257 - i, 257 - j);
    end
end

a = a / (4 * 10 * 10);

for i = 1:10
    for j = 11:246
        b = b + img(i,j) + img(257 - i,j) + img(j , i) + img(j , 257 - i);
    end
end

for i = 11:246
    for j = 11:246
        b = b + img(i,j);
    end
end

b = b / (256*256 - 4*10*10);

Tnew = (a + b) / 2;

while( Told ~= Tnew)
    sum1 = 0;
    sum2 = 0;

    count1 = 0;
    count2 = 0;
    
    for i = 1:256
        for j = 1:256
            if img(i,j) < Tnew
                sum1 = sum1 + img(i,j);
                count1 = count1 + 1;
            else
                sum2 = sum2 + img(i,j);
                count2 = count2 + 1;
            end
        end
    end
    
    a = sum1/count1;
    b = sum2/count2;
    
    Told = Tnew;
    
    Tnew = (a + b)/2;
    
end

newimg = zeros(dim);

for i = 1:256
    for j = 1:256
        if img(i,j) > Tnew
            newimg(i,j) = 256;
        else
            newimg(i,j) = 0;
        end
    end
end

imshow(uint8(newimg)); 