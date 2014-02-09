N=10;
x=1:N;
xodd=1:N/2;
xeven=1:N/2;

% I want to send the values of xeven to a simulink model
% as a signal. How?

for i=1:N
    if (mod(i,2)==0)
        xodd(ceil(i/2))=x(i);
    else
        xeven(ceil(i/2))=x(i);
    end 
end

evenTime  = 1:numel(xeven);
xeven = [evenTime' , xeven'];
% ts = timeseries(xeven);

sim('firstmodel',xeven)