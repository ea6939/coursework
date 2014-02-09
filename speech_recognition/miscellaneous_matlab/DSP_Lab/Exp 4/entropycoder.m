% entropy calculation/average number of bits for a compressed sequence 

% sample v + prob + code from lab handout
v1_prob = 0.2;
v2_prob = 0.1;
v3_prob = 0.05;
v4_prob = 0.65;
v_prob = [v1_prob v2_prob v3_prob v4_prob];

v1_bits = 2;
v2_bits = 3;
v3_bits = 3;
v4_bits = 1;
v_bits = [v1_bits v2_bits v3_bits v4_bits];

k = 10; % length of sequence
n = 4; % range of sequence
sequence = randsample(n,k,true,v_prob);
% ^ creates a sequences of those symbols with the appropriate probabilities

% find the average number of bits of each element of the sequence
average_number_of_bits = 0;
sum = 0;

for i = 1:k
    sum = sum + v_bits(sequence(i));
end

average_number_of_bits = sum/k;

% TODO: find the probability of each symbol
v1_prob_experimental = 0;
v2_prob_experimental = 0;
v3_prob_experimental = 0;
v4_prob_experimental = 1;
v_prob_experimental = [v1_prob_experimental v2_prob_experimental v3_prob_experimental v4_prob_experimental];

% find the entropy of the code
entropy = 0;
sum = 0;

for i = 1:n
    plogp = -v_prob_experimental(i) * log2(v_prob_experimental(i));
    sum = sum + plogp;
end

entropy = sum;