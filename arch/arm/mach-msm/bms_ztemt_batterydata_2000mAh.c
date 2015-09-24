#include <linux/mfd/pm8xxx/pm8921-bms.h>

static struct single_row_lut fcc_temp = {
	.x		= {-20, -10, 0, 25, 40, 45, 50, 60},
	.y		= {2036, 2042, 2041, 2046, 2047, 2040, 2038, 2039},
	.cols	= 8
};

static struct single_row_lut fcc_sf = {
	.x		= {0},
	.y		= {100},
	.cols	= 1
};

static struct sf_lut rbatt_sf = {
	.rows		= 30,
	.cols		= 8,
	.row_entries		= {-20, -10, 0, 25, 40, 45, 50, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1},
	.sf		= {
				{1095, 453, 237, 100, 85, 83, 82, 82},
				{1095, 453, 237, 100, 85, 83, 82, 82},
				{1097, 458, 242, 102, 87, 85, 83, 82},
				{1081, 458, 246, 106, 90, 87, 85, 84},
				{1067, 457, 247, 111, 92, 89, 86, 85},
				{1054, 452, 243, 116, 95, 92, 89, 87},
				{1048, 447, 238, 120, 99, 95, 92, 90},
				{1046, 447, 235, 117, 102, 98, 95, 92},
				{1054, 448, 235, 107, 96, 95, 93, 91},
				{1071, 453, 236, 102, 88, 87, 85, 84},
				{1093, 457, 238, 103, 88, 85, 83, 83},
				{1124, 465, 243, 104, 88, 87, 85, 84},
				{1158, 478, 248, 107, 91, 88, 86, 85},
				{1205, 493, 255, 110, 93, 90, 88, 86},
				{1262, 513, 265, 110, 92, 90, 88, 86},
				{1360, 538, 276, 106, 88, 86, 85, 83},
				{1532, 574, 283, 105, 88, 86, 85, 84},
				{1652, 608, 286, 106, 89, 87, 85, 84},
				{1608, 615, 283, 105, 88, 86, 85, 84},
				{1290, 560, 267, 103, 88, 86, 84, 84},
				{1425, 583, 275, 106, 89, 86, 85, 84},
				{1594, 611, 285, 108, 90, 87, 85, 85},
				{1843, 647, 300, 110, 91, 88, 86, 86},
				{2189, 698, 318, 111, 92, 89, 87, 86},
				{2701, 773, 342, 111, 90, 88, 86, 85},
				{3525, 891, 372, 111, 90, 88, 86, 85},
				{4989, 1150, 421, 113, 92, 88, 87, 86},
				{8087, 2096, 519, 119, 94, 91, 89, 88},
				{16690, 5066, 815, 130, 101, 95, 93, 93},
				{46764, 18528, 3096, 174, 141, 116, 116, 136},
					}
};


static struct pc_temp_ocv_lut pc_temp_ocv = {
	.rows		= 31,
	.cols		= 8,
	.temp		= {-20, -10, 0, 25, 40, 45, 50, 60},
	.percent	= {100, 95, 90, 85, 80, 75, 70, 65, 60, 55, 50, 45, 40, 35, 30, 25, 20, 16, 13, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0},
	.ocv		= {
				{4334, 4333, 4332, 4326, 4320, 4318, 4316, 4312},
				{4220, 4240, 4248, 4252, 4249, 4248, 4247, 4244},
				{4147, 4177, 4188, 4194, 4192, 4191, 4191, 4188},
				{4082, 4117, 4132, 4141, 4138, 4138, 4138, 4135},
				{4022, 4061, 4078, 4090, 4088, 4087, 4087, 4084},
				{3968, 4006, 4024, 4041, 4040, 4040, 4040, 4037},
				{3920, 3957, 3973, 3995, 3996, 3996, 3996, 3994},
				{3876, 3914, 3928, 3950, 3953, 3954, 3955, 3953},
				{3839, 3877, 3891, 3905, 3909, 3911, 3912, 3910},
				{3809, 3844, 3858, 3869, 3870, 3871, 3872, 3870},
				{3783, 3815, 3830, 3841, 3842, 3842, 3843, 3841},
				{3762, 3791, 3806, 3818, 3819, 3820, 3820, 3818},
				{3742, 3772, 3786, 3799, 3801, 3801, 3801, 3800},
				{3724, 3755, 3770, 3782, 3784, 3785, 3785, 3782},
				{3706, 3739, 3758, 3766, 3764, 3765, 3764, 3760},
				{3687, 3721, 3743, 3747, 3741, 3740, 3737, 3730},
				{3666, 3699, 3723, 3726, 3720, 3718, 3716, 3709},
				{3646, 3680, 3700, 3706, 3700, 3699, 3696, 3689},
				{3626, 3665, 3679, 3685, 3680, 3680, 3677, 3670},
				{3610, 3653, 3665, 3674, 3671, 3670, 3668, 3662},
				{3599, 3645, 3659, 3671, 3669, 3667, 3665, 3659},
				{3587, 3635, 3651, 3667, 3665, 3664, 3662, 3655},
				{3571, 3622, 3642, 3660, 3659, 3659, 3656, 3649},
				{3552, 3606, 3629, 3649, 3648, 3649, 3647, 3637},
				{3527, 3584, 3610, 3626, 3622, 3627, 3624, 3610},
				{3497, 3551, 3578, 3586, 3580, 3589, 3585, 3568},
				{3457, 3504, 3527, 3532, 3527, 3539, 3535, 3516},
				{3400, 3436, 3459, 3464, 3458, 3475, 3471, 3449},
				{3323, 3341, 3366, 3371, 3365, 3390, 3386, 3360},
				{3201, 3206, 3230, 3229, 3222, 3262, 3259, 3228},
				{3000, 3000, 3000, 3000, 3000, 3000, 3000, 3000}
	}
};

struct bms_battery_data ztemt_2000mAh_data = {
	.fcc				= 2000,
	.fcc_temp_lut			= &fcc_temp,
	.fcc_sf_lut				= &fcc_sf,
	.pc_temp_ocv_lut		= &pc_temp_ocv,
	.rbatt_sf_lut			= &rbatt_sf,
	.default_rbatt_mohm	= 180
};
