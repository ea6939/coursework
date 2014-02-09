function quoi = entropy_calculator(Q, num_levels)

prob_level_m = zeros([1,num_levels]);
sum_level_m = zeros([1,num_levels]);
scale_factor = max(max(Q),abs(min(Q)));
value_of_level_m = zeros([1,num_levels]);

for m = 1:num_levels
   value_of_level_m(m) = scale_factor*((m*2/num_levels) - 1);
end

for q = 1:num_levels
   for r = 1:length(Q)
       if (threshold(Q(r),value_of_level_m(q)) == 1)
           sum_level_m(q) = sum_level_m(q) + 1;
       end
   end
   prob_level_m(q) =  sum_level_m(q) / length(Q);
end

entropy = 0;
sum_plogp = 0;
plogp = 0;

for i = 1:num_levels
    if (prob_level_m(i) ~= 0)
    plogp = -prob_level_m(i) * log2(prob_level_m(i));
    sum_plogp = sum_plogp + plogp;
    end
end

entropy = sum_plogp;
quoi = entropy;

end
