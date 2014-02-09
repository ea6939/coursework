% chorus.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

% chorus
f1 = 30;
f2 = 10;
f3 = 5;
fs = 8192; 
%load the audio
audio = wavread('comp.wav');
audio = audio';
N = length(audio);
table = 1:N;
delaytable1 = sin(2*pi*f1*table/fs)+1;

delaytable2 = sin(2*pi*f2*table/fs)+1;

delaytable3 = sin(2*pi*f3*table/fs)+1;
% sample time range of interest from -5 to 5 %

result = zeros(size(audio));

new_value = 0;
for i = 3:length(result)
    if (mod((i - delaytable1(i)),1) ~= 0)
        next = ceil(i - delaytable1(i));
        previous = floor(i - delaytable1(i));
        new_value = (audio(next)-audio(previous))*next + audio(previous);
    else
        new_value = audio(i - delaytable1(i));
    end
    
    result(i) = result(i) + new_value/20000;
end

new_value = 0;
for i = 3:length(result)
    if (mod((i - delaytable2(i)),1) ~= 0)
        next = ceil(i - delaytable2(i));
        previous = floor(i - delaytable2(i));
        new_value = (audio(next)-audio(previous))*next + audio(previous);
    else
        new_value = audio(i - delaytable2(i));
    end
    
    result(i) = result(i) + new_value/20000;
end

new_value = 0;
for i = 3:length(result)
    if (mod((i - delaytable3(i)),1) ~= 0)
        next = ceil(i - delaytable3(i));
        previous = floor(i - delaytable3(i));
        new_value = (audio(next)-audio(previous))*next + audio(previous);
    else
        new_value = audio(i - delaytable3(i));
    end
    
    result(i) = result(i) + new_value/20000;
end

sound(result);
subplot(2,1,1), plot(audio);
subplot(2,1,2), plot(result);