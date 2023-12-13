% 定义向量 v1 和 v2
v1 = normalize(signal1(1:40));
v2 = normalize(signal2(1:40));
% v1 = signal1(1:40);
% v1scaleFactor = 1/ max(v1);
% v2 = signal2(1:40);
% v2scaleFactor = 1/ max(v2);
% 计算向量的点积
dot_product = dot(v1, v2);

% 计算向量的范数（模）
norm_v1 = norm(v1);
norm_v2 = norm(v2);

% 计算夹角的余弦值
cosine_angle = dot_product / (norm_v1 * norm_v2);

% 计算夹角（弧度）
angle_rad = acos(cosine_angle);

% 将弧度转换为度数
angle_deg = rad2deg(angle_rad);

fprintf('夹角（弧度）: %f\n', angle_rad);
fprintf('夹角（度数）: %f\n', angle_deg);