import { useState, useEffect } from 'react';
import { Link, useNavigate, useOutletContext } from 'react-router-dom';
import { useDispatch, useSelector } from 'react-redux';
import Loader from '../Loader';
import { toast } from 'react-toastify';
import AnimatedContainerPage from '../pages/AnimatedContainerPage';

import { useLoginMutation } from '../../slices/usersApiSlice';
import { setCredentials } from '../../slices/authSlice';

const LoginScreen = () => {
    const [user, setUser] = useState({
        email: '',
        password: '',
    });

    const [smallScreen] = useOutletContext();

    const navigate = useNavigate();
    const dispatch = useDispatch();

    const [login, { isLoading, isError, error }] = useLoginMutation();

    const { userInfo } = useSelector((state) => state.auth);

    useEffect(() => {
        if (userInfo) {
            navigate('/overview');
        }
    }, [navigate, userInfo]);

    const onchange = (e) => {
        setUser({ ...user, [e.target.name]: e.target.value });
    };

    const onSubmit = async (e) => {
        e.preventDefault();
        try {
            const res = await login(user).unwrap();
            dispatch(setCredentials({ ...res }));
            navigate('/overview');
        } catch (err) {
            toast.error(err?.data?.message || err.error);
        }
    };

    return (
        <AnimatedContainerPage>
            <div className='container'>
                <div className='form-container form-centered'>
                    <h1>
                        <span className='text-primary'>Sign In</span>
                    </h1>

                    <form onSubmit={onSubmit}>
                        <div className='form-group'>
                            <label htmlFor='email'>Email Address</label>
                            <input
                                type='email'
                                name='email'
                                className='form-input-text'
                                value={user.email}
                                onChange={onchange}
                                required
                            />

                            <label htmlFor='password'>Password</label>
                            <input
                                type='password'
                                name='password'
                                className='form-input-text'
                                value={user.password}
                                onChange={onchange}
                                required
                            />
                        </div>

                        <div
                            className='form-group form-centered'
                            style={{
                                padding: '1rem',
                            }}
                        >
                            <input
                                type='submit'
                                value='Login'
                                className={
                                    smallScreen ? 'btn btn-big' : 'btn btn-dark'
                                }
                            />

                            <p
                                style={{
                                    padding: '0.6rem',
                                }}
                            >
                                Don't have an account?{' '}
                                <Link to='/register'>Register</Link>
                            </p>
                        </div>
                    </form>
                </div>
            </div>
        </AnimatedContainerPage>
    );
};

export default LoginScreen;
