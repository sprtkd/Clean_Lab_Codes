clear all;
clc;
stream=0;
while(1)
    a = input('Generate bit for BSC (y/n)? ','s')

    if strcmpi(a,'y')
        v=round(mod((rand()*1000),1));
        stream=[stream v]
    else
        disp('You opted to exit');
        break;
    end
end