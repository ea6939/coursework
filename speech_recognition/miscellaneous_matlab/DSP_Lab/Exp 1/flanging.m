% flanging.m
% ECSE 490 - DSP Lab
% Group 1 - Isabel Helleur and Loren Lugosch
% Experiment 1 - February 6, 2013

f0 = 30; %5Hz
fs = 8192; 
%load the audio
audio = wavread('comp.wav');
audio = audio';
N = length(audio);
table = 1:N;
delaytable = sin(2*pi*f0*table/fs)+1;
% sample time range of interest from -5 to 5 %

result = zeros(size(audio));

new_value = 0;

for i = 3:length(result)
    if (mod((i - delaytable(i)),1) ~= 0)
        next = ceil(i - delaytable(i));
        previous = floor(i - delaytable(i));
        new_value = (audio(next)-audio(previous))*next + audio(previous);
    else
        new_value = audio(i - delaytable(i));
    end
    
    result(i) = (new_value + audio(i))/20000;
end

sound(result);
subplot(2,1,1), plot(audio);
subplot(2,1,2), plot(result);