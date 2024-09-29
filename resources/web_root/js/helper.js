document.addEventListener('DOMContentLoaded', function() {
    // URL 파라미터 파싱
    const urlParams = new URLSearchParams(window.location.search);
    const baseGrantURL = urlParams.get('base_grant_url');
    const userContinueURL = urlParams.get('user_continue_url');
    const clientIP = urlParams.get('client_ip');
    const clientMAC = urlParams.get('client_mac');
    const nodeMAC = urlParams.get('node_mac');

    // 디버깅 정보 표시
    document.getElementById('baseGrantURL').textContent = baseGrantURL || 'N/A';
    document.getElementById('userContinueURL').textContent = userContinueURL || 'N/A';
    document.getElementById('clientIP').textContent = clientIP || 'N/A';
    document.getElementById('clientMAC').textContent = clientMAC || 'N/A';
    document.getElementById('nodeMAC').textContent = nodeMAC || 'N/A';

    // 폼 제출 이벤트 리스너
    document.getElementById('loginForm').addEventListener('submit', function(e) {
        e.preventDefault();

        const studentId = document.getElementById('studentId').value;
        const password = document.getElementById('password').value;

        // 서버로 데이터 전송
        fetch('http://your-server-url/login', {
            method: 'POST',
            headers: {
                'Content-Type': 'application/json',
            },
            body: JSON.stringify({
                studentId: studentId,
                password: password,
                clientIP: clientIP,
                clientMAC: clientMAC,
                nodeMAC: nodeMAC
            })
        })
        .then(response => response.json())
        .then(data => {
            if (data.success) {
                // 로그인 성공 시 Meraki 인증 URL로 리디렉션
                window.location.href = baseGrantURL + '?continue_url=' + userContinueURL;
            } else {
                alert('로그인 실패: ' + data.message);
            }
        })
        .catch(error => {
            console.error('Error:', error);
            alert('로그인 중 오류가 발생했습니다.');
        });
    });
});