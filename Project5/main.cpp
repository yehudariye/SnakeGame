#include <windows.h>
#include <thread>
#include <atomic>
#include <chrono>
#include "Board.h"
#include "Snake.h"

// ===========================
// Game Constants
// ===========================
const int CELL_SIZE = 10;
const int GRID_WIDTH = 100;
const int GRID_HEIGHT = 100;

// ===========================
// Global Game State
// ===========================
Snake* g_snake = nullptr;
Board* g_board = nullptr;
std::atomic<bool> g_running{ true };
std::thread g_gameThread;

// ===========================
// Draws the game grid and snake
// ===========================
void DrawGame(HDC hdc)
{
    // Draw grid lines
    HPEN gridPen = CreatePen(PS_SOLID, 1, RGB(220, 220, 220));
    SelectObject(hdc, gridPen);

    for (int x = 0; x <= GRID_WIDTH; ++x)
    {
        MoveToEx(hdc, x * CELL_SIZE, 0, nullptr);
        LineTo(hdc, x * CELL_SIZE, GRID_HEIGHT * CELL_SIZE);
    }
    for (int y = 0; y <= GRID_HEIGHT; ++y)
    {
        MoveToEx(hdc, 0, y * CELL_SIZE, nullptr);
        LineTo(hdc, GRID_WIDTH * CELL_SIZE, y * CELL_SIZE);
    }
    DeleteObject(gridPen);

    // Draw the snake
    HBRUSH snakeBrush = CreateSolidBrush(RGB(0, 180, 0));
    for (const auto& node : g_snake->get_body())
    {
        int x = std::get<0>(node);
        int y = std::get<1>(node);
        RECT r = { x * CELL_SIZE, y * CELL_SIZE, (x + 1) * CELL_SIZE, (y + 1) * CELL_SIZE };
        FillRect(hdc, &r, snakeBrush);
    }
    DeleteObject(snakeBrush);
}

// ===========================
// Game loop thread that updates snake movement
// ===========================
void GameLoopThread(HWND hwnd)
{
    while (g_running)
    {
        if (g_snake)
        {
            if (!g_snake->move()) {
                InvalidateRect(hwnd, nullptr, FALSE); // Request redraw
            }
            else {
                g_running = false;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(200)); // Control speed
    }
}

// ===========================
// Window procedure - handles input and painting
// ===========================
LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
    switch (msg)
    {
    case WM_PAINT:
    {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);
        DrawGame(hdc);
        EndPaint(hwnd, &ps);
        break;
    }

    case WM_KEYDOWN:
        if (g_snake)
        {
            // Handle arrow key input for direction change
            switch (wParam)
            {
            case VK_LEFT:
                g_snake->change_diraction(l);
                break;
            case VK_RIGHT:
                g_snake->change_diraction(r);
                break;
            case VK_UP:
                g_snake->change_diraction(u);
                break;
            case VK_DOWN:
                g_snake->change_diraction(d);
                break;
            }
            InvalidateRect(hwnd, nullptr, FALSE); // Redraw after direction change
        }
        break;

    case WM_DESTROY:
        PostQuitMessage(0); // Exit message loop
        break;

    default:
        return DefWindowProc(hwnd, msg, wParam, lParam);
    }

    return 0;
}

// ===========================
// WinMain - application entry point
// ===========================
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE, LPSTR, int nCmdShow)
{
    // Initialize game components
    g_board = new Board(blink); // 'blink' should be defined or replaced
    g_snake = new Snake(GRID_WIDTH / 2, GRID_HEIGHT / 2, 5);

    // Define window class
    WNDCLASS wc = {};
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = L"SnakeGameClass";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    RegisterClass(&wc);

    // Create the main game window
    HWND hwnd = CreateWindowEx(
        0,
        wc.lpszClassName,
        L"Snake Game",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT, CW_USEDEFAULT,
        GRID_WIDTH * CELL_SIZE + 16,  // Width with padding
        GRID_HEIGHT * CELL_SIZE + 39, // Height with padding
        nullptr, nullptr,
        hInstance, nullptr
    );

    ShowWindow(hwnd, nCmdShow);

    // Start the game loop in a separate thread
    g_gameThread = std::thread(GameLoopThread, hwnd);

    // Main Windows message loop
    MSG msg;
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Cleanup resources
    g_running = false;
    if (g_gameThread.joinable())
        g_gameThread.join();

    delete g_snake;
    delete g_board;

    return 0;
}
