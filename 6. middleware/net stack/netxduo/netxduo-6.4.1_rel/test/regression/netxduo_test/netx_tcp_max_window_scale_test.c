/* This NetX test concentrates on the TCP MAX windows scale operation.  */

#include   "tx_api.h"
#include   "nx_api.h"
#include   "nx_tcp.h"    
#include   "nx_ip.h"        
extern void    test_control_return(UINT status);

#if defined(NX_ENABLE_TCP_WINDOW_SCALING) && defined(__PRODUCT_NETXDUO__) && !defined(NX_DISABLE_IPV4)

#define     DEMO_STACK_SIZE    2048

/* Define the ThreadX and NetX object control blocks...  */

static TX_THREAD               ntest_0;
static TX_THREAD               ntest_1;
static NX_PACKET_POOL          pool_0;
static NX_IP                   ip_0;
static NX_IP                   ip_1;
static NX_TCP_SOCKET           client_socket;
static NX_TCP_SOCKET           server_socket;

/* Define the counters used in the demo application...  */

static ULONG                   syn_counter;

static ULONG                   error_counter;

/* Define thread prototypes.  */

static void    ntest_0_entry(ULONG thread_input);
static void    ntest_1_entry(ULONG thread_input);
static void    ntest_0_connect_received(NX_TCP_SOCKET *server_socket, UINT port);
static void    ntest_0_disconnect_received(NX_TCP_SOCKET *server_socket);
extern void    _nx_ram_network_driver(struct NX_IP_DRIVER_STRUCT *driver_req);
extern void    _nx_ram_network_driver_1500(struct NX_IP_DRIVER_STRUCT *driver_req);
static void    my_tcp_packet_receive(NX_IP *ip_ptr, NX_PACKET *packet_ptr);
extern USHORT  _nx_ip_checksum_compute(NX_PACKET *packet_ptr, ULONG protocol, 
                                       UINT data_length, ULONG* src_ip_addr,
                                       ULONG* dest_ip_addr);
extern UINT    (*advanced_packet_process_callback)(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT *operation_ptr, UINT *delay_ptr);
static UINT    my_packet_process(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT *operation_ptr, UINT *delay_ptr);


/* Define what the initial system looks like.  */

#ifdef CTEST
VOID test_application_define(void *first_unused_memory)
#else
void           netx_tcp_max_window_scale_test_application_define(void *first_unused_memory)
#endif
{
CHAR       *pointer;
UINT       status;

    /* Setup the working pointer.  */
    pointer = (CHAR *) first_unused_memory;

    error_counter = 0;
    syn_counter = 0;

    /* Create the main thread.  */
    tx_thread_create(&ntest_0, "thread 0", ntest_0_entry, 0,  
                     pointer, DEMO_STACK_SIZE, 
                     3, 3, TX_NO_TIME_SLICE, TX_AUTO_START);

    pointer = pointer + DEMO_STACK_SIZE;

    /* Create the main thread.  */
    tx_thread_create(&ntest_1, "thread 1", ntest_1_entry, 0,  
                     pointer, DEMO_STACK_SIZE, 
                     4, 4, TX_NO_TIME_SLICE, TX_AUTO_START);

    pointer = pointer + DEMO_STACK_SIZE;

    /* Initialize the NetX system.  */
    nx_system_initialize();

    /* Create a packet pool.  */
    status = nx_packet_pool_create(&pool_0, "NetX Main Packet Pool", 512, pointer, 8192);
    pointer = pointer + 8192;

    if(status)
        error_counter++;

    /* Create an IP instance.  */
    status = nx_ip_create(&ip_0, "NetX IP Instance 0", IP_ADDRESS(1, 2, 3, 4), 0xFFFFFF00UL, &pool_0, _nx_ram_network_driver,
                          pointer, 2048, 1);
    pointer = pointer + 2048;

    if(status)
        error_counter++;

    /* Create another IP instance.  */
    status = nx_ip_create(&ip_1, "NetX IP Instance 1", IP_ADDRESS(1, 2, 3, 5), 0xFFFFFF00UL, &pool_0, _nx_ram_network_driver_1500,
                          pointer, 2048, 1);
    pointer = pointer + 2048;

    if(status)
        error_counter++;

    /* Enable ARP and supply ARP cache memory for IP Instance 0.  */
    status = nx_arp_enable(&ip_0, (void *) pointer, 1024);
    pointer = pointer + 1024;

    if(status)
        error_counter++;

    /* Enable ARP and supply ARP cache memory for IP Instance 1.  */
    status = nx_arp_enable(&ip_1, (void *) pointer, 1024);
    pointer = pointer + 1024;

    /* Check ARP enable status.  */
    if(status)
        error_counter++;

    /* Enable TCP processing for both IP instances.  */
    status = nx_tcp_enable(&ip_0);
    if(status)
        error_counter++;

    status = nx_tcp_enable(&ip_1);
    if(status)
        error_counter++;

}

/* Define the test threads.  */

static void    ntest_0_entry(ULONG thread_input)
{
UINT       status;
ULONG      actual_status;

    /* Print out test information banner.  */
    printf("NetX Test:   TCP MAX Window Scale Test.................................");

    /* Check for earlier error.  */
    if(error_counter)
    {
        printf("ERROR!\n");
        test_control_return(1);
    }

    /* Ensure the IP instance has been initialized.  */
    status = nx_ip_status_check(&ip_0, NX_IP_INITIALIZE_DONE, &actual_status, NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Create a socket.  */
    status = nx_tcp_socket_create(&ip_0, &server_socket, "Server Socket", 
                                  NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE, ((1<<30)-1),
                                  NX_NULL, ntest_0_disconnect_received);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Setup this thread to listen.  */
    status = nx_tcp_server_socket_listen(&ip_0, 12, &server_socket, 5, ntest_0_connect_received);

    /* Check for error.  */
    if(status)
        error_counter++;

    ip_0.nx_ip_tcp_packet_receive = my_tcp_packet_receive;

    /* The window scale value is modified to 0xFF which is larger than 14. */
    status = nx_tcp_server_socket_accept(&server_socket, NX_IP_PERIODIC_RATE);

    if(status)
        error_counter++;

    if(syn_counter == 1)
    {
        /*Check whether the connection has crashed*/
        if((client_socket.nx_tcp_socket_state != NX_TCP_ESTABLISHED) || (server_socket.nx_tcp_socket_state != NX_TCP_ESTABLISHED))
            error_counter++;

        /* Check the windows size.  */
        if ((client_socket.nx_tcp_socket_rx_window_default != ((1<<30)-1)) || (client_socket.nx_tcp_socket_rx_window_current  != ((1<<30)-1)) ||
            (server_socket.nx_tcp_socket_rx_window_default != ((1<<30)-1)) || (server_socket.nx_tcp_socket_rx_window_current  != ((1<<30)-1)))            
            error_counter++;
    }
    else
        error_counter++;

    /* Disconnect the server socket.  */
    status = nx_tcp_socket_disconnect(&server_socket, NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Unaccept the server socket.  */
    status = nx_tcp_server_socket_unaccept(&server_socket);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Relisten.  */
    status = nx_tcp_server_socket_relisten(&ip_0, 12, &server_socket);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* The window scale option is removed from syn packet. */
    status = nx_tcp_server_socket_accept(&server_socket, 1 * NX_IP_PERIODIC_RATE);

    if(status)
        error_counter++;

    /*Check whether the connection has crashed*/
    if((client_socket.nx_tcp_socket_state != NX_TCP_ESTABLISHED) || (server_socket.nx_tcp_socket_state != NX_TCP_ESTABLISHED))
        error_counter++;

    /* Check the windows size.  */
    if ((client_socket.nx_tcp_socket_rx_window_default != 0xFFFF) || (client_socket.nx_tcp_socket_rx_window_current  != 0xFFFF) ||
        (server_socket.nx_tcp_socket_rx_window_default != 0xFFFF) || (server_socket.nx_tcp_socket_rx_window_current  != 0xFFFF))            
        error_counter++;

    /* Disconnect the server socket.  */
    status = nx_tcp_socket_disconnect(&server_socket, 1 * NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Unaccept the server socket.  */
    status = nx_tcp_server_socket_unaccept(&server_socket);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Delete the socket.  */
    status = nx_tcp_socket_delete(&server_socket);

    /* Check for error.  */
    if(status)
        error_counter++;
}

static void    ntest_1_entry(ULONG thread_input)
{
UINT       status;

    /* Create a socket.  */
    status = nx_tcp_socket_create(&ip_1, &client_socket, "Client Socket", 
                                  NX_IP_NORMAL, NX_FRAGMENT_OKAY, NX_IP_TIME_TO_LIVE, ((1<<30)-1),
                                  NX_NULL, NX_NULL);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Set the window size no less than 2^30. */
    client_socket.nx_tcp_socket_rx_window_default = ((ULONG)1<<31) - 1;

    /* Bind the socket.  */
    status = nx_tcp_client_socket_bind(&client_socket, 12, NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /*To handle the syn packet.*/
    advanced_packet_process_callback = my_packet_process;

    /* Attempt to connect the socket.  */ 
    status = nx_tcp_client_socket_connect(&client_socket, IP_ADDRESS(1, 2, 3, 4), 12, 2 * NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Disconnect this socket.  */
    status = nx_tcp_socket_disconnect(&client_socket, NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Attempt to connect the socket.  */ 
    status = nx_tcp_client_socket_connect(&client_socket, IP_ADDRESS(1, 2, 3, 4), 12, 2 * NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Disconnect this socket.  */
    status = nx_tcp_socket_disconnect(&client_socket, 1 * NX_IP_PERIODIC_RATE);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Unbind the socket.  */
    status = nx_tcp_client_socket_unbind(&client_socket);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Delete the socket.  */
    status = nx_tcp_socket_delete(&client_socket);

    /* Check for error.  */
    if(status)
        error_counter++;

    /* Determine if the test was successful.  */
    if((error_counter != 0) || (syn_counter != 2))
    {
        printf("ERROR!\n");
        test_control_return(1);
    }
    else
    {
        printf("SUCCESS!\n");
        test_control_return(0);
    }

}

static void    ntest_0_connect_received(NX_TCP_SOCKET *socket_ptr, UINT port)
{

    /* Check for the proper socket and port.  */
    if((socket_ptr != &server_socket) || (port != 12))
        error_counter++;
}

static void    ntest_0_disconnect_received(NX_TCP_SOCKET *socket)
{

    /* Check for proper disconnected socket.  */
    if(socket != &server_socket)
        error_counter++;
}


static UINT    my_packet_process(NX_IP *ip_ptr, NX_PACKET *packet_ptr, UINT *operation_ptr, UINT *delay_ptr)
{
NX_TCP_HEADER   *tcp_header_ptr;
ULONG           *option_word_1;
ULONG           *option_word_2;
ULONG           checksum;
ULONG           *source_ip, *dest_ip;

    tcp_header_ptr = (NX_TCP_HEADER*)((packet_ptr -> nx_packet_prepend_ptr) + 20);
    option_word_1 = (ULONG *)(tcp_header_ptr + 1);
    option_word_2 = option_word_1 + 1;
    NX_CHANGE_ULONG_ENDIAN(tcp_header_ptr -> nx_tcp_header_word_3);

    /* If this is a tcp packet but not an ARP packet or other kind packet. */
    if(packet_ptr -> nx_packet_length >= 40)
    {
        /* Chcek whether it is a SYN packet.  */
        if((tcp_header_ptr -> nx_tcp_header_word_3 & NX_TCP_SYN_BIT) && !(tcp_header_ptr -> nx_tcp_header_word_3 & NX_TCP_ACK_BIT) && !(tcp_header_ptr -> nx_tcp_header_word_3 & NX_TCP_RST_BIT))
        {   
            NX_CHANGE_ULONG_ENDIAN(tcp_header_ptr -> nx_tcp_header_word_3);
                                                                          
            NX_CHANGE_ULONG_ENDIAN(*option_word_1);
            NX_CHANGE_ULONG_ENDIAN(*option_word_2);

            if (syn_counter == 0)
            {

                /* Modify the Window scale option to 0xFF which is larger than 14.  */
                *option_word_2 = *option_word_2 | 0x0000FF00;
            }
            else
            {

                /* Remove window scale option. */
                *option_word_2 = NX_TCP_OPTION_END;
            }

            NX_CHANGE_ULONG_ENDIAN(*option_word_1);                             
            NX_CHANGE_ULONG_ENDIAN(*option_word_2);

            /*Put the packet pointer to tcp*/
            packet_ptr -> nx_packet_prepend_ptr += sizeof(NX_IPV4_HEADER);
            packet_ptr -> nx_packet_length -= sizeof(NX_IPV4_HEADER);

            /* Calculate the TCP checksum.  */
            tcp_header_ptr -> nx_tcp_header_word_4 = 0;

            dest_ip = &client_socket.nx_tcp_socket_connect_ip.nxd_ip_address.v4;
            source_ip = &client_socket. nx_tcp_socket_connect_interface -> nx_interface_ip_address;
            checksum = _nx_ip_checksum_compute(packet_ptr, NX_PROTOCOL_TCP,
                                               packet_ptr -> nx_packet_length,
                                               source_ip, dest_ip);
            checksum = ~checksum & NX_LOWER_16_MASK;

            /* Move the checksum into header.  */
            NX_CHANGE_ULONG_ENDIAN(tcp_header_ptr -> nx_tcp_header_word_4);
            tcp_header_ptr -> nx_tcp_header_word_4 = (checksum << NX_SHIFT_BY_16);
            NX_CHANGE_ULONG_ENDIAN(tcp_header_ptr -> nx_tcp_header_word_4);


            packet_ptr -> nx_packet_prepend_ptr -= sizeof(NX_IPV4_HEADER);
            packet_ptr -> nx_packet_length += sizeof(NX_IPV4_HEADER);

        }
        else
            NX_CHANGE_ULONG_ENDIAN(tcp_header_ptr -> nx_tcp_header_word_3);
    }
    return NX_TRUE;
 }

static void    my_tcp_packet_receive(NX_IP *ip_ptr, NX_PACKET *packet_ptr)
{
NX_TCP_HEADER   *header_ptr;
ULONG           *option_word_2;

    header_ptr = (NX_TCP_HEADER *)packet_ptr -> nx_packet_prepend_ptr;
    option_word_2 = ((ULONG *)(header_ptr + 1)) + 1;
    NX_CHANGE_ULONG_ENDIAN(header_ptr -> nx_tcp_header_word_3);

    /* Server receives a SYN packet.  */
    if((header_ptr -> nx_tcp_header_word_3 & NX_TCP_SYN_BIT) && !(header_ptr -> nx_tcp_header_word_3 & NX_TCP_ACK_BIT) && !(header_ptr -> nx_tcp_header_word_3 & NX_TCP_RST_BIT))
    {
        NX_CHANGE_ULONG_ENDIAN(*option_word_2);
        syn_counter++;

        NX_CHANGE_ULONG_ENDIAN(*option_word_2);
    }

    NX_CHANGE_ULONG_ENDIAN(header_ptr -> nx_tcp_header_word_3);

    /* Pass the packet to the default function.  */
    _nx_tcp_packet_receive(ip_ptr, packet_ptr);      
}
#else      

#ifdef CTEST
VOID test_application_define(void *first_unused_memory)
#else
void           netx_tcp_max_window_scale_test_application_define(void *first_unused_memory)
#endif
{

    /* Print out test information banner.  */
    printf("NetX Test:   TCP MAX Window Scale Test.................................N/A\n");

    test_control_return(3);
}
#endif
