
#include "parser-test.h"

#if 0 /* PARSER_EMBEDDED_CONFIG */
default linux

label linux
kernel ./pxe/de-ad-de-ad-be-ef.vmlinuz
append command line
initrd=./pxe/de-ad-de-ad-be-ef.initrd
#endif

void run_test(struct parser_test *test)
{
	struct discover_boot_option *opt;
	struct discover_context *ctx;

	test_read_conf_embedded_url(test, "tftp://host/dir/pxelinux.cfg/C0A8");

	test_set_event_source(test);
	test_set_event_param(test->ctx->event, "bootfile", "dir/pxe");
	test_set_event_param(test->ctx->event, "tftp", "host");
	test_set_event_param(test->ctx->event, "mac", "12:34:56:78:9a:bc");
	test_set_event_param(test->ctx->event, "ip", "192.168.0.1");

	test_run_parser(test, "pxe");

	ctx = test->ctx;

	check_boot_option_count(ctx, 1);
	opt = get_boot_option(ctx, 0);

	check_name(opt, "linux");
	check_args(opt, "command line");

	check_resolved_url_resource(opt->boot_image,
			"tftp://host/dir/./pxe/de-ad-de-ad-be-ef.vmlinuz");
	check_resolved_url_resource(opt->initrd,
			"tftp://host/dir/./pxe/de-ad-de-ad-be-ef.initrd");
}
