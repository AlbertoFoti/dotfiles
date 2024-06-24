import React from 'react';
import { useSelector, useDispatch } from 'react-redux';
import PropTypes from 'prop-types';
import { Link, useNavigate, useLocation } from 'react-router-dom';
import { motion } from 'framer-motion';
import TabElement from './TabElement';
import { clearCredentials } from '../../slices/authSlice';
import { useLogoutMutation } from '../../slices/usersApiSlice';

const NavBar = ({ title, icon }) => {
    const { userInfo } = useSelector((state) => state.auth);

    const dispatch = useDispatch();
    const navigate = useNavigate();
    const location = useLocation();

    const pathname = location.pathname;

    const [logout] = useLogoutMutation();

    const onLogout = async () => {
        try {
            const res = await logout().unwrap();
            dispatch(clearCredentials({ ...res }));
            navigate('/');
        } catch (err) {
            toast.error(err?.data?.message || err.error);
        }
    };

    const authLinks = (
        <div
            style={{
                display: 'flex',
                flexDirection: 'row',
                justifyContent: 'space-between',
                alignItems: 'center',
            }}
        >
            <li>
                <a href='#profile-modal' className='modal-trigger'>
                    <ion-icon name='person-outline'></ion-icon>
                </a>
            </li>

            <li>
                <a href='#settings-modal' className='modal-trigger'>
                    <ion-icon name='settings-outline'></ion-icon>
                </a>
            </li>

            <li>
                <a href='#fire-modal' className='modal-trigger'>
                    <ion-icon name='trophy-outline'></ion-icon>
                </a>
            </li>

            <li
                style={{
                    display: 'flex',
                    alignItems: 'center',
                    justifyContent: 'center',
                    flexDirection: 'row',
                }}
            >
                <button className='btn btn-small' onClick={onLogout}>
                    <ion-icon name='log-out-outline'></ion-icon>
                    <span className='hide-sm'>Logout</span>
                </button>
            </li>
        </div>
    );

    const guestLinks = (
        <div>
            <li>
                <Link to={`/register`}>Register</Link>
            </li>
            <li>
                <Link to={`/login`}>Login</Link>
            </li>
            <li>
                <Link to={`/about`}>
                    <ion-icon
                        name='information-circle-outline'
                        className='hide-on-med-and-up'
                    ></ion-icon>
                    <span className='text-main hide-on-small-only'>About</span>
                </Link>
            </li>
        </div>
    );

    return (
        <motion.div
            initial={{ opacity: 0 }}
            animate={{ opacity: 1 }}
            exit={{ opacity: 0 }}
            transition={{ duration: 1.5 }}
        >
            <div>
                <nav
                    className='nav-extended'
                    style={{
                        padding: '0 0.5rem',
                        marginBottom: '0rem',
                    }}
                >
                    <div
                        className='nav-wrapper'
                        style={{
                            padding: '0 0rem',
                            marginBottom: '0rem',
                        }}
                    >
                        <Link
                            to='/'
                            className='left logo flex-center'
                            style={{
                                paddingLeft: '0.7rem',
                            }}
                        >
                            <span
                                className='material-symbols-outlined nav-bar-icon flex'
                                style={{
                                    paddingRight: '0.5rem',
                                }}
                            >
                                <ion-icon name={icon}></ion-icon>
                            </span>
                            <span className='hide-sm hide-on-small-only nav-bar-title'>
                                {title}
                            </span>
                            <span
                                className='hide-sm hide-on-med-and-up nav-bar-title'
                                style={{
                                    fontSize: '15px',
                                }}
                            >
                                {title}
                            </span>
                        </Link>

                        <ul id='nav-mobile' className='right'>
                            {userInfo !== null ? authLinks : guestLinks}
                        </ul>
                    </div>

                    {userInfo !== null ? (
                        <div
                            className='nav-content'
                            style={{
                                padding: '0 0rem',
                                margin: '0 0rem',
                            }}
                        >
                            <ul
                                className='my-tabs'
                                style={{
                                    padding: '0 0rem',
                                    margin: '0 0rem',
                                    display: 'flex',
                                    flexDirection: 'row',
                                    justifyContent: 'space-around',
                                    alignItems: 'center',
                                }}
                            >
                                <TabElement
                                    text='Overview'
                                    linkTo='/overview'
                                    icon='bar-chart-outline'
                                    currentLocation={pathname}
                                />
                                <TabElement
                                    text='Net worth'
                                    linkTo='/networth'
                                    icon='cash-outline'
                                    currentLocation={pathname}
                                />
                                <TabElement
                                    text='Cashflow'
                                    linkTo='/cashflow'
                                    icon='card-outline'
                                    currentLocation={pathname}
                                />
                                <TabElement
                                    text='Investments'
                                    linkTo='/investments'
                                    icon='trending-up-outline'
                                    currentLocation={pathname}
                                />
                                <TabElement
                                    text='Allocation'
                                    linkTo='/assetallocation'
                                    icon='pie-chart-outline'
                                    currentLocation={pathname}
                                />
                                <TabElement
                                    text='Forecasts'
                                    linkTo='/forecasts'
                                    icon='calendar-outline'
                                    currentLocation={pathname}
                                />
                                <TabElement
                                    text='Transactions'
                                    linkTo='/transactions'
                                    icon='pricetags-outline'
                                    currentLocation={pathname}
                                />
                            </ul>
                        </div>
                    ) : null}
                </nav>
            </div>
        </motion.div>
    );
};

NavBar.propTypes = {
    title: PropTypes.string.isRequired,
    icon: PropTypes.string,
};

NavBar.defaultProps = {
    title: 'Navbar Title',
    icon: 'fa-solid fa-question',
};

export default NavBar;
