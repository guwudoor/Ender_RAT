#pragma once
int init_winsock();
void wipe_it();
struct addrinfo *result;
void handle_command(CLIENT&, string&);