% Plot results of moving average for different lengths of filter
load('temperature_data.mat') % data recorded from Keil's printf window

% create moving average filters
buffer_5 = ones(1,5)/5;
buffer_10 = ones(1,10)/10;
buffer_20 = ones(1,20)/20;

% average the data
temps_5 = conv(temps,buffer_5);
temps_10 = conv(temps,buffer_10);
temps_20 = conv(temps,buffer_20);

%%
subplot(4,1,1)
plot(temps)
title('Raw data')
axis([1 88 33 37])
grid on
%%
subplot(4,1,2)
plot(temps_5)
title('Length-5 moving average')
axis([1 88 33 37])
grid on
%%
subplot(4,1,3)
plot(temps_10)
title('Length-10 moving average')
axis([1 88 33 37])
grid on
%%
subplot(4,1,4)
plot(temps_20)
title('Length-20 moving average')
axis([1 88 33 37])
grid on