#include <linux/init.h>
#include <linux/module.h>
#include <linux/usb/input.h>
#include <linux/hid.h>

MODULE_AUTHOR("Oxnz <yunxinyi@gmail.com>");
MODULE_DESCRIPTION("X7 usb mouse driver");
MODULE_LICENSE("GPL");

struct x7 {
	char name[128];
	char phys[64];
	struct usb_device *usbdev;
	struct input_dev *hiddev;
	struct urb *irq;
	signed char *data;
	dma_addr_t data_dma;
};

static void x7_irq(struct urb *urb) {
	printk(KERN_ALERT "urb irq");
}

static int x7_open(struct input_dev *dev) {
	printk(KERN_ALERT "open");
	return 0;
}

static void x7_close(struct input_dev *dev) {
}

static int x7_probe(struct usb_interface *intf, const struct usb_device_id *id) {
	printk(KERN_ALERT "probe");
	struct usb_device *dev = interface_to_usbdev(intf);
	struct usb_host_interface *interface;
	struct usb_endpoint_descriptor *endpoint;
	struct usb_mouse *mouse;
	struct input_dev *indev;
	int pipe, maxp;

	interface = intf->cur_altsetting;
	if (interface->desc.bNumEndpoints != 1)
		return -ENODEV;
	endpoint = &interface->endpoint[0].desc;
	if (!usb_endpoint_is_int_in(endpoint))
		return -ENODEV;
	printk(KERN_ALERT "OK");

	/*
	pipe = usb_rcvintpipe(dev, endpoint->bEndpointAddress);
	maxp = usb_maxpacket(dev, pipe, usb_pipeout(pipe));
	mouse = kzalloc(sizeof(struct usb_mouse), GFP_KERNEL);
	input_dev = input_allocate_device();
	if (!mouse || !input_dev)
		goto fail;
	mouse->data = usb_buffer_alloc(dev, GFP_ATOMIC, &mouse_data_dma);
	if (!mouse->data)
		goto fail;
	mouse->irq = usb_alloc_urb(0, GFP_KERNEL);
	if (!mouse->irq)
		goto fail;
	mouse->usbdev = dev;
	mouse->dev = input_dev;
	if (dev->manufacturer)
		strlcat(mouse->name, dev->manufacturer, sizeof(mouse->name));
	*/
	return 0;
}

static void x7_disconnect(struct usb_interface *intf) {
	printk(KERN_ALERT "disconnect");
}

static struct usb_device_id x7_id_table[] = {
	{ USB_INTERFACE_INFO(USB_INTERFACE_CLASS_HID,
			USB_INTERFACE_SUBCLASS_BOOT,
			USB_INTERFACE_PROTOCOL_MOUSE) },
	{}
};

MODULE_DEVICE_TABLE(usb, x7_id_table);

static struct usb_driver x7_driver = {
	.name	= "x7mice",
	.probe	= x7_probe,
	.disconnect = x7_disconnect,
	.id_table = x7_id_table,
};

static int __init x7_init(void) {
	int ret = usb_register(&x7_driver);
	if (!ret)
		printk(KERN_ALERT "YES");
	printk(KERN_ALERT "x7 mouse driver init\n");
	return ret;
}

static void __exit x7_exit(void) {
	printk(KERN_ALERT "x7 mouse driver unload\n");
	usb_deregister(&x7_driver);
}

module_init(x7_init);
module_exit(x7_exit);
