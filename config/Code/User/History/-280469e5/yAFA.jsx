import React from 'react';
import ReactDOM from 'react-dom/client';
import { BrowserRouter, Routes, Route } from 'react-router-dom';

import store from './store.js';
import { Provider } from 'react-redux';

import App from './App.jsx';
import './css/index.css';

import HomeScreen from './screens/HomeScreen.jsx';
import LoginScreen from './components/auth/LoginScreen.jsx';
import RegisterScreen from './components/auth/RegisterScreen.jsx';

import PricingScreen from './screens/PricingScreen.jsx';
import CommunityScreen from './screens/CommunityScreen.jsx';
import AboutScreen from './screens/AboutScreen.jsx';
import ContactsScreen from './screens/ContactsScreen.jsx';

import PrivateRoute from './components/PrivateRoute.jsx';
//import ProfileScreen from './screens/ProfileScreen.jsx';
import OverviewPage from './screens/tabPages/OverviewPage.jsx';
import NetWorthPage from './screens/tabPages/NetWorthPage.jsx';
import CashflowPage from './screens/tabPages/CashflowPage.jsx';
import InvestmentsPage from './screens/tabPages/InvestmentsPage.jsx';
import AssetallocationPage from './screens/tabPages/AssetallocationPage.jsx';
import ForecastsPage from './screens/tabPages/ForecastsPage.jsx';
import TransactionsPage from './screens/tabPages/TransactionsPage.jsx';

ReactDOM.createRoot(document.getElementById('root')).render(
    <Provider store={store}>
        <React.StrictMode>
            <BrowserRouter>
                <Routes>
                    <Route path='/' element={<App />}>
                        <Route index={true} path='/' element={<HomeScreen />} />
                        <Route path='/login' element={<LoginScreen />} />
                        <Route path='/register' element={<RegisterScreen />} />
                        <Route path='/pricing' element={<PricingScreen />} />
                        <Route
                            path='/community'
                            element={<CommunityScreen />}
                        />
                        <Route path='/about' element={<AboutScreen />} />
                        <Route path='/contacts' element={<ContactsScreen />} />

                        <Route path='' element={<PrivateRoute />}>
                            <Route
                                path='/overview'
                                element={<OverviewPage />}
                            />
                            <Route
                                path='/networth'
                                element={<NetWorthPage />}
                            />
                            <Route
                                path='/cashflow'
                                element={<CashflowPage />}
                            />
                            <Route
                                path='/investments'
                                element={<InvestmentsPage />}
                            />
                            <Route
                                path='/assetallocation'
                                element={<AssetallocationPage />}
                            />
                            <Route
                                path='/forecasts'
                                element={<ForecastsPage />}
                            />
                            <Route
                                path='/transactions'
                                element={<TransactionsPage />}
                            />
                        </Route>
                    </Route>
                </Routes>
            </BrowserRouter>
        </React.StrictMode>
    </Provider>
);
