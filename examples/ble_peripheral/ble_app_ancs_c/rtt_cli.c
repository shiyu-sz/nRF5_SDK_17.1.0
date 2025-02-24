
#include "nrf_cli.h"
#include "nrf_cli_rtt.h"
#include "nrf_cli_types.h"
#include "nrf_log.h"
#include <time.h>
#include "bsp.h"

extern void key_event(bsp_event_t event);

/* Counter timer. */
APP_TIMER_DEF(m_timer_0);

/** @brief Command line interface instance. */
#define CLI_EXAMPLE_LOG_QUEUE_SIZE  (4)

NRF_CLI_RTT_DEF(m_cli_rtt_transport);
NRF_CLI_DEF(m_cli_rtt,
            "rtt_cli:~$ ",
            &m_cli_rtt_transport.transport,
            '\n',
            CLI_EXAMPLE_LOG_QUEUE_SIZE);

static void timer_handle(void * p_context)
{
    nrf_cli_process(&m_cli_rtt);
}

void cli_init(void)
{
    ret_code_t ret;

    ret = nrf_cli_init(&m_cli_rtt, NULL, true, true, NRF_LOG_SEVERITY_INFO);
    APP_ERROR_CHECK(ret);

    ret = nrf_cli_start(&m_cli_rtt);
    APP_ERROR_CHECK(ret);

    ret = app_timer_create(&m_timer_0, APP_TIMER_MODE_REPEATED, timer_handle);
    APP_ERROR_CHECK(ret);

    ret = app_timer_start(m_timer_0, APP_TIMER_TICKS(100), NULL);
    APP_ERROR_CHECK(ret);
}

static void f1_callback(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_DEFAULT, "run f1_callback\n");
    key_event(BSP_EVENT_DISCONNECT);
}
NRF_CLI_CMD_REGISTER(f1, NULL, "f1", f1_callback);

static void f2_callback(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_DEFAULT, "run f2_callback\n");
    key_event(BSP_EVENT_WHITELIST_OFF);
}
NRF_CLI_CMD_REGISTER(f2, NULL, "f2", f2_callback);

static void f3_callback(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_DEFAULT, "run f3_callback\n");
    key_event(BSP_EVENT_KEY_0);
}
NRF_CLI_CMD_REGISTER(f3, NULL, "f3", f3_callback);

static void f4_callback(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_DEFAULT, "run f4_callback\n");
    key_event(BSP_EVENT_KEY_1);
}
NRF_CLI_CMD_REGISTER(f4, NULL, "f4", f4_callback);

static void f5_callback(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_DEFAULT, "run f5_callback\n");
    key_event(BSP_EVENT_KEY_2);
}
NRF_CLI_CMD_REGISTER(f5, NULL, "f5", f5_callback);

static void f6_callback(nrf_cli_t const * p_cli, size_t argc, char **argv)
{
    nrf_cli_fprintf(p_cli, NRF_CLI_DEFAULT, "run f6_callback\n");
    key_event(BSP_EVENT_KEY_3);
}
NRF_CLI_CMD_REGISTER(f6, NULL, "f6", f6_callback);
