
#include <stdio.h>

#define MAX_TICKETS 5

// 1. Khai bao cau truc ve
struct Ticket {
    int ticket_id;
    char event_name[50];
    double price;
    int is_vip;
};

// 2. Khai bao nguyen mau ham
double calculate_ticket_price(double price, int is_vip);

int find_ticket(const struct Ticket list[],
                int total_tickets, int ticket_id);

void display_tickets(const struct Ticket list[],
                     int total_tickets);

int add_ticket(struct Ticket list[], int total_tickets,
               struct Ticket new_ticket);

int delete_ticket(struct Ticket list[], int total_tickets,
                  int ticket_id);

int main() {
    // 3. Khoi tao danh sach ban dau gom 2 ve
    struct Ticket list[MAX_TICKETS] = {
        {101, "Concert_A", 500000, 1},
        {102, "Concert_B", 300000, 0}
    };

    int total_tickets = 2;

    struct Ticket new_ticket;

    printf("===== DANH SACH VE BAN DAU =====\n");
    display_tickets(list, total_tickets);

    // 4. Tinh gia ve VIP
    printf("\n===== TINH GIA VE VIP =====\n");
    printf("Gia goc: %.0f VND\n", 500000.0);
    printf("Gia thanh toan: %.0f VND\n",
           calculate_ticket_price(500000.0, 1));

    // 5. Them ve moi
    printf("\n===== KIEM THU THEM VE =====\n");

    new_ticket.ticket_id = 103;
    sprintf(new_ticket.event_name, "Concert_C");
    new_ticket.price = 400000;
    new_ticket.is_vip = 1;

    total_tickets = add_ticket(list, total_tickets, new_ticket);

    new_ticket.ticket_id = 104;
    sprintf(new_ticket.event_name, "Concert_D");
    new_ticket.price = 250000;
    new_ticket.is_vip = 0;

    total_tickets = add_ticket(list, total_tickets, new_ticket);

    new_ticket.ticket_id = 105;
    sprintf(new_ticket.event_name, "Concert_E");
    new_ticket.price = 350000;
    new_ticket.is_vip = 0;

    total_tickets = add_ticket(list, total_tickets, new_ticket);

    // Luc nay danh sach da co 5 ve, thu them mot ve nua
    new_ticket.ticket_id = 106;
    sprintf(new_ticket.event_name, "Concert_F");
    new_ticket.price = 200000;
    new_ticket.is_vip = 0;

    total_tickets = add_ticket(list, total_tickets, new_ticket);

    printf("\n===== DANH SACH SAU KHI THEM =====\n");
    display_tickets(list, total_tickets);

    // 6. Xoa ma ve khong ton tai
    printf("\n===== KIEM THU XOA VE KHONG TON TAI =====\n");
    total_tickets = delete_ticket(list, total_tickets, 999);

    // 7. Xoa ve hop le
    printf("\n===== KIEM THU XOA VE 103 =====\n");
    total_tickets = delete_ticket(list, total_tickets, 103);

    printf("\n===== DANH SACH SAU KHI XOA =====\n");
    display_tickets(list, total_tickets);

    return 0;
}

// 8. Ham tinh gia ve
double calculate_ticket_price(double price, int is_vip) {
    if (is_vip == 1) {
        return price * 1.2;
    }

    return price;
}

// 9. Ham tim kiem ve, tra ve index hoac -1
int find_ticket(const struct Ticket list[],
                int total_tickets, int ticket_id) {
    int i;

    for (i = 0; i < total_tickets; i++) {
        if (list[i].ticket_id == ticket_id) {
            return i;
        }
    }

    return -1;
}

// 10. Ham hien thi danh sach ve
void display_tickets(const struct Ticket list[],
                     int total_tickets) {
    int i;

    if (total_tickets == 0) {
        printf("Danh sach ve dang rong!\n");
        return;
    }

    printf("--------------------------------------------------------------------------\n");
    printf("%-10s %-20s %-15s %-12s %-15s\n",
           "Ma ve", "Ten su kien", "Gia goc",
           "Loai ve", "Gia thanh toan");
    printf("--------------------------------------------------------------------------\n");

    for (i = 0; i < total_tickets; i++) {
        printf("%-10d %-20s %-15.0f %-12s %-15.0f\n",
               list[i].ticket_id,
               list[i].event_name,
               list[i].price,
               list[i].is_vip == 1 ? "VIP" : "Thuong",
               calculate_ticket_price(list[i].price,
                                      list[i].is_vip));
    }

    printf("--------------------------------------------------------------------------\n");
    printf("Tong so ve: %d/%d\n", total_tickets, MAX_TICKETS);
}

// 11. Ham them ve moi
int add_ticket(struct Ticket list[], int total_tickets,
               struct Ticket new_ticket) {
    if (total_tickets >= MAX_TICKETS) {
        printf("Danh sach ve da day! Khong the them ve %d.\n",
               new_ticket.ticket_id);
        return total_tickets;
    }

    if (find_ticket(list, total_tickets,
                    new_ticket.ticket_id) != -1) {
        printf("Ma ve %d da ton tai! Khong the them.\n",
               new_ticket.ticket_id);
        return total_tickets;
    }

    list[total_tickets] = new_ticket;

    printf("Them ve %d thanh cong!\n", new_ticket.ticket_id);

    return total_tickets + 1;
}

// 12. Ham xoa ve
int delete_ticket(struct Ticket list[], int total_tickets,
                  int ticket_id) {
    int index;
    int i;

    if (total_tickets == 0) {
        printf("Danh sach ve dang rong, khong the xoa!\n");
        return total_tickets;
    }

    index = find_ticket(list, total_tickets, ticket_id);
    if (index == -1) {
        printf("Khong tim thay ma ve %d!\n", ticket_id);
        return total_tickets;
    }

    for (i = index; i < total_tickets - 1; i++) { list[i] = list[i + 1];
    }
    printf("Xoa ve %d thanh cong!\n", ticket_id);

    return total_tickets - 1;
}
