% Given data
velocities = [1001.7, 975.0, 978.3, 988.3, 978.7, 988.9, 1000.3, 979.2, 968.9, 983.5, 979.2, 985.5, 999.2, 985.6];
n = length(velocities);

% Degrees of freedom
df = n - 1;

% Calculate sample standard deviation
sample_std = std(velocities);

% Calculate chi-square critical values for a 99% confidence interval
alpha = 0.01; % significance level (1 - confidence level)
chi_square_lower = chi2inv(alpha/2, df);
chi_square_upper = chi2inv(1 - alpha/2, df);

% Calculate confidence interval for standard deviation
confidence_interval_lower = sqrt((n - 1) * sample_std^2 / chi_square_upper);
confidence_interval_upper = sqrt((n - 1) * sample_std^2 / chi_square_lower);

% Display the result
fprintf('99%% Confidence Interval for Standard Deviation: (%.4f, %.4f)\n', confidence_interval_lower, confidence_interval_upper);
