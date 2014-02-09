% interface
% use this to run the program on whatever speech file you want

% input signal
%X = sin(0.001*(1:15000));
% for d=1:15000
% X(d)=3;
% end
% for d=1:480
% X(d)=0;
% end
% noise=0.1*(randn(size(X)));
% X=X+noise;
% X = wavread('test_noisy.WAV');

original = wavread('once_upon_a_time.wav');
original = original';
noisy = original + 0.01*randn(size(original));
warning('off','all');

speech_start=22150; % sample where speech starts

cleaned_up = remove_noise_main(noisy,speech_start);

subplot(2,1,1), plot(noisy);
subplot(2,1,2), plot(cleaned_up);