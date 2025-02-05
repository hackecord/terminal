// Copyright (c) Microsoft Corporation.
// Licensed under the MIT license.

#pragma once
#include <winrt/Microsoft.UI.Xaml.Controls.h>
#include "Pane.h"

class Tab : public std::enable_shared_from_this<Tab>
{
public:
    Tab(const GUID& profile, const winrt::Microsoft::Terminal::TerminalControl::TermControl& control);

    // Called after construction to setup events with weak_ptr
    void BindEventHandlers(const winrt::Microsoft::Terminal::TerminalControl::TermControl& control) noexcept;

    winrt::Microsoft::UI::Xaml::Controls::TabViewItem GetTabViewItem();
    winrt::Windows::UI::Xaml::UIElement GetRootElement();
    winrt::Microsoft::Terminal::TerminalControl::TermControl GetActiveTerminalControl() const;
    std::optional<GUID> GetFocusedProfile() const noexcept;

    bool IsFocused() const noexcept;
    void SetFocused(const bool focused);

    void Scroll(const int delta);

    bool CanSplitPane(winrt::TerminalApp::SplitState splitType);
    void SplitPane(winrt::TerminalApp::SplitState splitType, const GUID& profile, winrt::Microsoft::Terminal::TerminalControl::TermControl& control);

    void UpdateIcon(const winrt::hstring iconPath);

    void ResizeContent(const winrt::Windows::Foundation::Size& newSize);
    void ResizePane(const winrt::TerminalApp::Direction& direction);
    void NavigateFocus(const winrt::TerminalApp::Direction& direction);

    void UpdateSettings(const winrt::Microsoft::Terminal::Settings::TerminalSettings& settings, const GUID& profile);
    winrt::hstring GetActiveTitle() const;
    void SetTabText(const winrt::hstring& text);

    void ClosePane();

    WINRT_CALLBACK(Closed, winrt::Windows::Foundation::EventHandler<winrt::Windows::Foundation::IInspectable>);
    DECLARE_EVENT(ActivePaneChanged, _ActivePaneChangedHandlers, winrt::delegate<>);

private:
    std::shared_ptr<Pane> _rootPane{ nullptr };
    std::shared_ptr<Pane> _activePane{ nullptr };
    winrt::hstring _lastIconPath{};

    bool _focused{ false };
    winrt::Microsoft::UI::Xaml::Controls::TabViewItem _tabViewItem{ nullptr };

    void _MakeTabViewItem();
    void _Focus();

    void _AttachEventHandlersToControl(const winrt::Microsoft::Terminal::TerminalControl::TermControl& control);
    void _AttachEventHandlersToPane(std::shared_ptr<Pane> pane);
};
