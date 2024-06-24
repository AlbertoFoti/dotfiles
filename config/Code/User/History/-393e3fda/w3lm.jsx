import { useSelector, useDispatch } from 'react-redux';
import { useNavigate } from 'react-router-dom';
import { useLogoutMutation } from '../slices/usersApiSlice';
import { clearCredentials } from '../slices/authSlice';
import NavBar from './navigation/NavBar';

const Header = () => {
    const { userInfo } = useSelector((state) => state.auth);

    const dispatch = useDispatch();
    const navigate = useNavigate();

    const [logoutApiCall] = useLogoutMutation();

    const logoutHandler = async () => {
        try {
            await logoutApiCall().unwrap();
            dispatch(clearCredentials());
            navigate('/login');
        } catch (err) {
            console.log(err?.data?.message || err.error);
        }
    };

    return (
        <header className=''>
            <NavBar title='Money Tracker' icon='cash-outline' />
        </header>
    );
};

export default Header;
