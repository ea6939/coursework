% average bit error rate

average_BER_variance_1 = 0;
average_BER_variance_2 = 0;
average_BER_variance_3 = 0;

BER_variance_1 = 0*(1:100);
BER_variance_2 = 0*(1:100);
BER_variance_3 = 0*(1:100);

for trial = 1:100
    group1 = wavread('NoisySig.wav');
    original = wavread('CleanSig.wav');
    noise = 1.1*randn(size(group1));
    group1 = group1 + noise;
    equalization;
    bitcounter;
    BER_variance_1(trial) =  bit_error_rate;
end

average_BER_variance_1 = sum(BER_variance_1)/100;
    
for trial = 1:100
    group1 = wavread('NoisySig.wav');
    original = wavread('CleanSig.wav');
    noise = 2*randn(size(group1));
    group1 = group1 + noise;
    equalization;
    bitcounter;
    BER_variance_2(trial) =  bit_error_rate;
end

average_BER_variance_2 = sum(BER_variance_2)/100;
   
for trial = 1:100
    group1 = wavread('NoisySig.wav');
    original = wavread('CleanSig.wav');
    noise = 4*randn(size(group1));
    group1 = group1 + noise;
    equalization;
    bitcounter;
    BER_variance_3(trial) =  bit_error_rate;
end

average_BER_variance_3 = sum(BER_variance_3)/100;