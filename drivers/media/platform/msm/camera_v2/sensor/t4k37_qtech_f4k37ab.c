#include "msm_sensor.h"
//#define T4K37_SENSOR_NAME "t4k37"
#define T4K37_QTECH_F4K37AB_SENSOR_NAME "t4k37_qtech_f4k37ab"
DEFINE_MSM_MUTEX(t4k37_qtech_f4k37ab_mut);

#define T4K37_QTECH_F4K37AB_DEBUG
#undef CDBG
#ifdef T4K37_QTECH_F4K37AB_DEBUG
#define CDBG(fmt, args...) pr_err(fmt, ##args)
#else
#define CDBG(fmt, args...) do { } while (0)
#endif
static struct msm_sensor_ctrl_t t4k37_qtech_f4k37ab_s_ctrl;

static struct msm_sensor_power_setting t4k37_qtech_f4k37ab_power_setting[] = {
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VIO,
		.config_val = 0,
		.delay = 5,
	},
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VANA,
		.config_val = 0,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VDIG,
		.config_val = 0,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_VREG,
		.seq_val = CAM_VAF,
		.config_val = 0,
		.delay = 5,
	},
	{
		.seq_type = SENSOR_CLK,
		.seq_val = SENSOR_CAM_MCLK,
		.config_val = 24000000,
		.delay = 10,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_STANDBY,
		.config_val = GPIO_OUT_LOW,
		.delay = 10,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_LOW,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_STANDBY,
		.config_val = GPIO_OUT_HIGH,
		.delay = 10,
	},
	{
		.seq_type = SENSOR_GPIO,
		.seq_val = SENSOR_GPIO_RESET,
		.config_val = GPIO_OUT_HIGH,
		.delay = 0,
	},
	{
		.seq_type = SENSOR_I2C_MUX,
		.seq_val = 0,
		.config_val = 0,
		.delay = 0,
	},
};

static struct v4l2_subdev_info t4k37_qtech_f4k37ab_subdev_info[] = {
	{
		.code   = V4L2_MBUS_FMT_SBGGR10_1X10,
		.colorspace = V4L2_COLORSPACE_JPEG,
		.fmt    = 1,
		.order    = 0,
	},
};

static const struct i2c_device_id t4k37_qtech_f4k37ab_i2c_id[] = {
	{T4K37_QTECH_F4K37AB_SENSOR_NAME, (kernel_ulong_t)&t4k37_qtech_f4k37ab_s_ctrl},
	{ }
};

static int32_t msm_t4k37_qtech_f4k37ab_i2c_probe(struct i2c_client *client,
	const struct i2c_device_id *id)
{
	return msm_sensor_i2c_probe(client, id, &t4k37_qtech_f4k37ab_s_ctrl);
}

static struct i2c_driver t4k37_qtech_f4k37ab_i2c_driver = {
	.id_table = t4k37_qtech_f4k37ab_i2c_id,
	.probe  = msm_t4k37_qtech_f4k37ab_i2c_probe,
	.driver = {
		.name = T4K37_QTECH_F4K37AB_SENSOR_NAME,
	},
};

static struct msm_camera_i2c_client t4k37_qtech_f4k37ab_sensor_i2c_client = {
	.addr_type = MSM_CAMERA_I2C_WORD_ADDR,
};

static const struct of_device_id t4k37_qtech_f4k37ab_dt_match[] = {
	{.compatible = "qcom,t4k37_qtech_f4k37ab", .data = &t4k37_qtech_f4k37ab_s_ctrl},
	{}
};

MODULE_DEVICE_TABLE(of, t4k37_qtech_f4k37ab_dt_match);

static struct platform_driver t4k37_qtech_f4k37ab_platform_driver = {
	.driver = {
		.name = "qcom,t4k37_qtech_f4k37ab",
		.owner = THIS_MODULE,
		.of_match_table = t4k37_qtech_f4k37ab_dt_match,
	},
};

static int32_t t4k37_qtech_f4k37ab_platform_probe(struct platform_device *pdev)
{
	int32_t rc = 0;
	const struct of_device_id *match;
	match = of_match_device(t4k37_qtech_f4k37ab_dt_match, &pdev->dev);
	rc = msm_sensor_platform_probe(pdev, match->data);
	return rc;
}

#if 1
//add by kwang
extern struct platform_driver msm_eeprom_platform_driver;
extern int32_t msm_eeprom_platform_probe(struct platform_device *pdev);
//end by kwang
#endif
static int __init t4k37_qtech_f4k37ab_init_module(void)
{
	int32_t rc = 0;
	CDBG("%s:%d\n", __func__, __LINE__);
	rc = platform_driver_probe(&t4k37_qtech_f4k37ab_platform_driver,
		t4k37_qtech_f4k37ab_platform_probe);
	#if 0  //jun add for debug OTP
	t4k37_qtech_f4k37ab_s_ctrl.func_tbl->sensor_power_down(&t4k37_qtech_f4k37ab_s_ctrl);
	#else
		if (!rc){
				rc = platform_driver_probe(&msm_eeprom_platform_driver,
				msm_eeprom_platform_probe);
			printk("jun after eeprom probe rc =%d\n",rc);
	              t4k37_qtech_f4k37ab_s_ctrl.func_tbl->sensor_power_down(&t4k37_qtech_f4k37ab_s_ctrl);
			}
        #endif
	if (!rc)
		return rc;
	pr_err("%s:%d rc %d\n", __func__, __LINE__, rc);
	return i2c_add_driver(&t4k37_qtech_f4k37ab_i2c_driver);
}

static void __exit t4k37_qtech_f4k37ab_exit_module(void)
{
	CDBG("%s:%d\n", __func__, __LINE__);
	if (t4k37_qtech_f4k37ab_s_ctrl.pdev) {
		msm_sensor_free_sensor_data(&t4k37_qtech_f4k37ab_s_ctrl);
		platform_driver_unregister(&t4k37_qtech_f4k37ab_platform_driver);
	} else
		i2c_del_driver(&t4k37_qtech_f4k37ab_i2c_driver);
	return;
}

static struct msm_sensor_ctrl_t t4k37_qtech_f4k37ab_s_ctrl = {
	.sensor_i2c_client = &t4k37_qtech_f4k37ab_sensor_i2c_client,
	.power_setting_array.power_setting = t4k37_qtech_f4k37ab_power_setting,
	.power_setting_array.size = ARRAY_SIZE(t4k37_qtech_f4k37ab_power_setting),
	.msm_sensor_mutex = &t4k37_qtech_f4k37ab_mut,
	.sensor_v4l2_subdev_info = t4k37_qtech_f4k37ab_subdev_info,
	.sensor_v4l2_subdev_info_size = ARRAY_SIZE(t4k37_qtech_f4k37ab_subdev_info),
};

module_init(t4k37_qtech_f4k37ab_init_module);
module_exit(t4k37_qtech_f4k37ab_exit_module);
MODULE_DESCRIPTION("t4k37_qtech_f4k37ab");
MODULE_LICENSE("GPL v2");